/* @file EFM8-USB-MIDI.c
 *
 * Main() for a USB-MIDI class-compliant device.
 *
 * MIDI ports are the hardware or virtual connections.
 * This design has two in and two out ports.
 * Port 0 is the virtual port we use to control the hardware (for IN) and send back
 * 	button-and-knob changes.
 * Port 1 is the physical port connected to UART1.
 *
 * USB MIDI OUT messages for port 1 are routed to UART1 for transmit.
 * The event part of the messages is stripped off and the three data bytes are
 * loaded into the UART's transmit buffer.
 *
 * Messages received on physical port 1 in have an event byte added and a USB
 * MIDI message is built from what was received, and that message is written
 * to the MIDI bulk IN endpoint.
 *
 **************************************************************************
 * DATA HANDLING, USB OUT ENDPOINTS.  (over endpoint 1)
 *
 * To start accepting MIDI packets over USB, we call USBD_Read() in the device
 * state change callback. This passes a user buffer and size to the endpoint
 * interrupt handler. The buffer is the same size as the endpoint's maximum packet
 * size.
 *
 * The host sends one or more MIDI packets, each four bytes, in each OUT transaction,
 * and the bytes are all written to the endpoint FIFO. When the OUT transaction
 * is complete, the endpoint interrupt handler is invoked. That handler copies
 * the contents of the endpoint FIFO into the user buffer.
 *
 * The transfer-complete callback is invoked when either the host has sent MAX
 * PACKET SIZE bytes or when all of the bytes in the transaction have been read
 * from the endpoint FIFO. At that time, the user buffer contains all of the
 * bytes from the OUT transaction, and we know how many bytes that is.
 *
 * In the callback, the bytes from the user buffer are read out and MIDI messages
 * are built from each group of four bytes. Each message is pushed to a software
 * message FIFO.
 *
 * In the main loop, that software message FIFO is popped and parsed. If it is
 * intended for the "onboard controls" (the LEDs in this test case, but could be
 * anything in a product), those controls are set. If the message is intended
 * for the hardware (serial) MIDI OUT port, a message of the correct size is
 * built and those bytes are pushed to the serial port transmit FIFO.
 *
 * Here is the rub. That serial port is much slower than USB and we can easily
 * swamp it with messages. Therefore, we must signal to the host that we must
 * wait for room in the serial MIDI transmit FIFO.
 *
 * It is not documented, but if the endpoint is enabled and its FIFO is filled,
 * the SIE will NAK any further OUT transactions until there is sufficient room
 * in the FIFO for the data.
 *
 * The trick to forcing that NAK, then, is to not read the endpoint FIFO, and
 * the only way to (not) do that is to not call USBD_Read() to re-arm the
 * endpoint. Not calling USBD_Read() means the interrupt handler sees the endpoint
 * as not receiving, and so it won't pop the endpoint FIFO, allowing it to fill
 * and ultimately let the SIE NAK any futher transactions. Any data in the FIFO
 * will be read out once the USBD_Read() is finally called.
 *
 * So when to call USBD_Read()?
 *
 * The limiting factor is space in the serial transmit FIFO. We need to ensure
 * that there's always enough space in it for at least one Endpoint Packet's
 * worth of messages. With max packet size set to 32, that's at most 8 messages,
 * which itself is at most 3 bytes per or 24 bytes total. We set the serial
 * transmit FIFO almost-full threshold to that level.
 *
 * Therefore:
 * a) The endpoint is "armed" at configuration end.
 * b) It gets "disarmed" when an OUT transaction is handled and its contents are
 * 	pushed to the MIDI message FIFO.
 * c) After popping the MIDI message FIFO, we parse the message, and if intended
 * 	for the serial port, we write it to the serial FIFO. That write function
 * 	returns true if there is enough room in the serial FIFO for another whole
 * 	USB packet of MIDI messages, we set a flag, and after all parsing is done,
 * 	we call USBD_Read() to arm the endpoint.
 *  If there were no messages intended for the serial port we arm the endpoint
 * 	anyway. In any event, if we call USBD_Read() and the endpoint is already
 * 	armed (by a previous call), that call just returns without doing anything.
 *
 **************************************************************************
 */

#include <SI_EFM8UB2_Register_Enums.h>  //!< SFR declarations
#include "InitDevice.h"					//!< Set up peripherals
#include "efm8_usb.h"					//!< Expose all functions in USB library
#include "rgb_led.h"					//!< LEDs are lit by PCA (in PWM mode)
#include "bsp_config.h"					//!< Define board specifics.
#include "joybutton.h"					//!< Joystick and button handling
#include "midi.h"						//!< MIDI defintions
#include "usb_midi.h"					//!< USB-MIDI definitions and functions
#include "midi_uart.h"					//!< serial-port MIDI support

/**
 * Global buffer for the OUT endpoint.
 * This is provided to USBD_Read() every time that function is called.
 * This is declared in callback.c.
 */
extern SI_SEGMENT_VARIABLE(EndpointBuffer[SLAB_USB_EP1OUT_MAX_PACKET_SIZE], uint8_t, SI_SEG_IDATA);

//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void SiLabs_Startup(void) {
	// $[SiLabs Startup]
	// [SiLabs Startup]$
}

/**
 * main() Routine
*/
int main(void) {
	USBMIDI_Message_t uimep;		//!< user interface MIDI events we write to the host
	USBMIDI_Message_t spmep;		//!< events received on serial MIDI in we write to the host
	USBMIDI_Message_t usbmep;		//!< events received from USB endpoint
	uint8_t MsgToUart[3];			//!< MIDI messages we write to the serial transmitter
	uint8_t MsgToUartSize;			//!< how many bytes in that message?
	joybuttonReport_t jbr;			//!< Report indicating state of joystick and buttons.
	bit LBState;					//!< the left button's immediate state, for toggle test
	bit RBState;					//!< the right button's immediate state, for toggle test
	bit CBState;					//!< joystick center button's immediate state, for toggle test
	bool usbIntsEnabled;			//!< set if they are
	bool roomInTxFifo;				//!< from call to MIDIUART_writeMessage()
	Color ledcolor;					//!< The color of the RGB LED

	// Call hardware initialization routine
	enter_DefaultMode_from_RESET();

	// Initialize some other stuff.
	LBState = 0;
	RBState = 0;
	CBState = 0;
	roomInTxFifo = 1;		// yes, there is, at the start of time

	// Clear the endpoint buffer, mainly for debug.
	// Use MsgToUartSize as the iterator so we don't have to declare another automatic.
	for (MsgToUartSize = 0; MsgToUartSize < SLAB_USB_EP1OUT_MAX_PACKET_SIZE; MsgToUartSize++) {
		EndpointBuffer[MsgToUartSize] = 0;
	}

	// Clear the MIDI events received from the USB endpoint, mainly for debug.
	usbmep.event = 0x00;
	usbmep.byte1 = 0x00;
	usbmep.byte2 = 0x00;
	usbmep.byte3 = 0x00;

	// Prepare the hardware MIDI port.
	MIDIUART_init();

	// Prepare the FIFO used for USB OUT transactions.
	USBMIDIFIFO_Init();

	// this is brute force.
	// for now, no point in going further until USB connects.
	while (USBD_GetUsbState() != USBD_STATE_CONFIGURED)
		;

	/*
	 * start timer 5 for joystick ADC convert-start.
	 */
	MsgToUartSize = SFRPAGE;
	SFRPAGE = CONFIG_PAGE;
	TMR5CN0_TR5 = 1;
	SFRPAGE = MsgToUartSize;

	// Forever.
	while (1) {
		// check the joystick and buttons for changes.
		JOYBUTTON_GetReport(&jbr);

		/*
		 * for now, if a button was pressed or the joystick was moved,
		 * send a Control Change message MIDI channel 1, and also do something
		 * fun to the RGB LED.
		 */
		if (jbr.Button == LEFT_BUTTON) {
			uimep.event = USB_MIDI_EVENT(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE); // CC on channel 1
			uimep.byte1 = MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0); // CC on channel 1
			uimep.byte2 = 80;		// The control to change.
			ledcolor.blue = 0x00;
			ledcolor.green = 0x00;
			if (LBState == 0) {
				ledcolor.red = 0x7F;
				uimep.byte3 = 0x7F;		// full
			} else {
				ledcolor.red = 0x00;
				uimep.byte3 = 0x00;
			}
			RGB_SetColor(ledcolor, 255);
			LBState = !LBState;
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Left Button

		if (jbr.Button == RIGHT_BUTTON) {
			uimep.event = USB_MIDI_EVENT(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE);
			uimep.byte1 = MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0); // CC on channel 1
			uimep.byte2 = 81;	// control to change.
			ledcolor.blue = 0x00;
			ledcolor.red = 0x00;
			if (RBState == 0) {
				ledcolor.green = 0x7F;
				uimep.byte3 = 0x7F;		// full
			} else {
				ledcolor.green = 0x00;
				uimep.byte3 = 0x00;
			}
			RGB_SetColor(ledcolor, 255);
			RBState = !RBState;
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Right Button

		if (jbr.Button == CENTER_BUTTON) {
			uimep.event = USB_MIDI_EVENT(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE);
			uimep.byte1 = MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0); // CC on channel 1
			uimep.byte2 = 82;	// control to change.
			if (CBState == 0) {
				ledcolor.green = 0x7F;
				ledcolor.blue = 0x7F;
				ledcolor.red = 0x7F;
				uimep.byte3 = 0x7F;		// full
			} else {
				ledcolor.green = 0x00;
				ledcolor.red = 0x00;
				ledcolor.blue = 0x00;
				uimep.byte3 = 0x00;
			}
			RGB_SetColor(ledcolor, 255);
			CBState = !CBState;
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Center Button

		if (jbr.X) {
			ledcolor.red = 0x00;
			ledcolor.green = 0x00;
			uimep.event = USB_MIDI_EVENT(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE);
			uimep.byte1 = MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0); // CC on channel 1
			uimep.byte2 = 83;
			uimep.byte3 = jbr.X;
			ledcolor.blue = jbr.X;
			RGB_SetColor(ledcolor, 255);
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Joystick X

		if (jbr.Y) {
			ledcolor.red = 0x00;
			ledcolor.green = 0x00;
			uimep.event = USB_MIDI_EVENT(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE);
			uimep.byte1 = MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0); // CC on channel 1
			uimep.byte2 = 84;
			uimep.byte3 = jbr.Y;
			ledcolor.blue = jbr.Y;
			RGB_SetColor(ledcolor, 255);
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Joystick Y

		/*
		 * Pop the USB MIDI message stack for the next event message and parse it.
		 * The MIDI cable number whether it should be sent on to the serial MIDI
		 * port, or whether it stays on board (to control LEDs).
		 * If the cable number is neither of those, the packet is dropped on
		 * the floor.
		 */
		if (USBMIDIFIFO_Pop(&usbmep)) {
			// if it targets the hardware port, just pass it along.
			// We don't care much about the particular event, just the port (Cable Number).
			// the buffer is only three bytes because the USB packet can only give us
			// up to three bytes at a time.
			if (USB_MIDI_CABLE_NUMBER(usbmep.event) == UART_CN) {
				MsgToUart[0] = usbmep.byte1;
				MsgToUart[1] = usbmep.byte2;
				MsgToUart[2] = usbmep.byte3;

				switch (USB_MIDI_CODE_INDEX_NUMBER(usbmep.event)) {
				case USB_MIDI_CIN_SYSEND1:
				case USB_MIDI_CIN_SINGLEBYTE:
					MsgToUartSize = 1;
					break;
				case USB_MIDI_CIN_SYSCOM2:
				case USB_MIDI_CIN_SYSEND2:
				case USB_MIDI_CIN_PROGCHANGE:
				case USB_MIDI_CIN_CHANPRESSURE:
					MsgToUartSize = 2;
					break;
				default:
					MsgToUartSize = 3;
					break;
				} // switch

				MIDIUART_writeMessage(MsgToUart, MsgToUartSize);

			} else if (USB_MIDI_CABLE_NUMBER(usbmep.event) == VIRTUAL_CN) {
				if (usbmep.byte1
						== MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0)) {
					switch (usbmep.byte2) {
					case 80: // left button
						ledcolor.green = usbmep.byte3 << 1;
						ledcolor.red = 0;
						ledcolor.blue = 0;
						break;
					case 81: // right button
						ledcolor.green = 0;
						ledcolor.red = usbmep.byte3 << 1;
						ledcolor.blue = 0;
						break;
					case 82: // joystick X
						ledcolor.green = 0;
						ledcolor.red = 0;
						ledcolor.blue = usbmep.byte3 << 1;
						break;
					case 83: // joystick Y
						ledcolor.green = 0; //midiInMsg.byte3 << 1;
						ledcolor.red = 0;
						ledcolor.blue = usbmep.byte3 << 1;
						break;
					} // switch
					RGB_SetColor(ledcolor, 255);
				} // event
			} // which cable number?

		} // if there's a message in the FIFO

		/* Re-arm the endpoint if there is space in the serial port transmit
		 * FIFO to accept any messages for it.
		 */
		roomInTxFifo = MIDIUART_isRoomInFifo();

		if (roomInTxFifo && !USBD_EpIsBusy(EP1OUT)) {
			USBD_Read(EP1OUT,
					&EndpointBuffer,
					SLAB_USB_EP1OUT_MAX_PACKET_SIZE,
					true);
		}

		/*
		 * Handle messages received on the hardware IN port.
		 * These get packetized by the serial receiver into the proper USB MIDI
		 * message format for sending to host on USB IN endpoint.
		 * We just pass along the packet.
		 */
		if (MIDIUART_readMessage(&spmep)) {
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &spmep, sizeof(spmep), false);
			if (usbIntsEnabled)
				USB_EnableInts();
		}

	} // main while(1) loop
} // main()
