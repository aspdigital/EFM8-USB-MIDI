/** @file EFM8-USB-MIDI.c
 *
 * Andy Peters, devel@latke.net (c) 2019
 * Many parts (c) Silicon Labs.
 *
 * A USB-MIDI class-compliant device, implemented in the Silicon Labs
 * EFM8UB2 devices. This design will run on the EFM8UB STK (SLSTK2001A).
 *
 * It uses v4.1.6 of the SiLabs 8051 SDK. (To prevent pain from referencing
 * library sources, the SiLabs libraries are included as part of the source
 * tarball.)
 *
 * The reader is encouraged to consult several documents for more details. It is
 * assumed that details of how MIDI works are understood, and as such are not
 * repeated here.
 *
 * A) The MIDI 1.0 specification at https://www.midi.org/specifications
 * B) The USB Audio Device Class specification at
 * 	https://usb.org/document-library/usb-audio-devices-rev-30-and-adopters-agreement
 * 	as the USB MIDI spec is "subclass" if you will of USB Audio
 * C) The USB MIDI Devices spec at https://usb.org/document-library/usb-midi-devices-10
 *
 **************************************************************************
 *
 * MIDI over USB transfers take place over Bulk endpoints. A USB Bulk OUT endpoint
 * is used to send MIDI messages to a device. A Bulk IN endpoint is used to send
 * messages back to the host.
 *
 **************************************************************************
 *
 * MIDI is a "streaming interface" associated with an Audio Class device. The
 * device must define an Audio Control interface and (to be useful) one or more
 * streaming interfaces. (The other streaming interfaces are audio samples in and
 * out.)
 *
 **************************************************************************
 *
 * In the USB MIDI world, MIDI ports can be either hardware or "virtual" connections.
 * These are my definitions, noted here so the reader understands what I mean.
 *
 * A hardware connection is via the standard serial MIDI port using DIN connectors.
 * A "virtual" connection is one that is otherwise handled in the device, that is,
 * not available on a DIN connector and in fact is never serialized or deserialized.
 *
 * MIDI has always supported the idea of "channels." A MIDI device can be configured
 * to listen to a single particular channel. On devices which use the serial MIDI
 * ports, that selection was done with a 16-position switch. Therefore, one MIDI
 * port could support (listen and talk) on one of 16 channels. The channels on MIDI
 * devices are counted from 1 to 16; however the status bytes of a message count
 * channels as 0 to 15. So be aware of this.
 *
 * Messages for the serial port MIDI can be 2 or 3 bytes, or possibly more for
 * SysEx messages. Messages have a "Status Byte" followed by "Data Bytes."
 *
 * USB MIDI expands on that idea with the concept of "cables." The USB pipe can
 * be thought of as a multiplexor, combining sixteen virtual cables onto one. Since
 * "cables" are not part of the MIDI spec, the USB MIDI implementation specifies
 * that all messages are sent in four-byte packets. The first byte is called the
 * "Packet Header." This header contains the Cable Number in the upper nybble,
 * which indicates which virtual cable is the message should go on, and a "Code
 * Index Number" (CIN) on the lower nybble. The CIN indicates the classification
 * of the other three bytes in the message packet.
 *
 * Since the Packet Header can address only 16 cables, this sets the limit on
 * messages that can be sent over one Endpoint. If more than 16 cables are needed
 * then two (or more) Bulk endpoints must be used.
 *
 * One can think of "cables" as "ports." Your MIDI device may have several MIDI
 * OUT jacks, each of which connects to something else over a cable. So I will
 * use "cable" and "port" somewhat interchangeably.
 *
 * There is nothing saying that IN Port 1 and OUT Port 1 must be related. From
 * the perspective of the computer, they are completely independent.
 *
 * The USB MIDI spec introduces the concept of "jacks." Jacks are how the MIDI
 * network is defined within a USB MIDI device. They are not necessarily the
 * physical DIN connectors on the back panel of a device, although they could be.
 * Please see the discussion in the USB MIDI spec for details. For this example,
 * the jacks define the path from the host to either the "front panel" (the LED)
 * or the hardware MIDI serial port, and from the buttons or the hardware MIDI
 * serial port back to the host. The jacks are defined in the device descriptors,
 * see descriptors.c for how this is done.
 *
 **************************************************************************
 *
 * This design has two in and two out ports.
 *
 * Ports 0 are virtual ports. Port 0 MIDI IN (which is USB OUT) is used to control
 * the device in some interesting way. On the EFM8 STK, the RGB LED is controlled
 * by MIDI messages from the host. Port 0 MIDI OUT) is used to send messages back
 * to the host. On the EFM8 STK, button  presses and joystick moves are sent back
 * to the host using Port 0 OUT (USB IN).
 *
 * Ports 1 is a standard serial MIDI port, using a UART at 31.25 bkps. On the EFM8
 * STK, UART1 is used for this port. The proper optoisolator is required on the
 * input. The EFM8 port pins have sufficient drive to turn on the LED in the
 * (receive port's) optoisolator through the standard series resistors.
 *
 * USB MIDI OUT messages for port 1 are handled as such: the packet header of the
 * USB messages is stripped off and the three data bytes are loaded into a FIFO
 * in front of the UART's transmit buffer.
 *
 * Messages received on physical port 1 in have an event byte added and a USB
 * MIDI message is built from what was received, and that message is written
 * to the MIDI bulk IN endpoint. Care is taken to ensure that messages that use
 * running status are handled correctly. (Running status are message without
 * a status byte, only the data bytes, with the understanding that the previous
 * status byte applies.)
 *
 **************************************************************************
 * DATA HANDLING, USB OUT ENDPOINT 1.
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
 * transmit FIFO almost-full threshold to half the endpoint packet size, to allow
 * for more elasticity.
 *
 * Therefore:
 * a) The endpoint is "armed" at configuration end (in the state-change callback).
 * b) It gets "disarmed" automatically by the library interrupt handler when an
 *  OUT transaction is handled and its contents are pushed to the MIDI message FIFO.
 * c) After popping the MIDI message FIFO, we parse the message, and if intended
 * 	for the serial port, we write it to the serial FIFO. That write function
 * 	returns true if there is enough room in the serial FIFO for another whole
 * 	USB packet of MIDI messages. If so, we set a flag, and after all parsing is done,
 * 	we call USBD_Read() to arm the endpoint.
 *  If there were no messages intended for the serial port we arm the endpoint
 * 	anyway. In any event, if we call USBD_Read() and the endpoint is already
 * 	armed (by a previous call), that call just returns without doing anything.
 *
 **************************************************************************
 * DATA HANDLING, USB IN ENDPOINT 1.
 *
 * Data returned to the host can come from either of two sources:
 * a) When any of the buttons are pressed or the joystick is wiggled, and
 * b) When a message is received from the hardware serial MIDI port.
 *
 * For the former: every time through the main loop the function JOYBUTTON_GetReport(&jbr)
 * is called. The report returned in jbr is parsed. Each button and the joystick
 * (both its button and the up/down/left/right) are separate "controls" and for
 * each a different USB MIDI control change message is built. The Cable Number is
 * set to zero to indicate to the host that the message came from the user interface,
 * not the serial port. Then that message is written to the host with USBD_Write().
 *
 * For the latter: every time through the main loop the function MIDIUART_readMessage(&spmep)
 * is called. The argument spmep is a USB-MIDI message packet. We don't do anything
 * with this packet here, so we just ship it off to the host with USBD_Write().
 * The message packet built in MIDIUART_readMessage() sets the Cable Number to 1
 * so the host knows that the source of the message was from the serial port and
 * not the user interface things on the board.
 *
 **************************************************************************
 * Hardware (standard 31.25 kbps serial) MIDI support.
 *
 * We fully support MIDI over old-school serial on DIN connectors. UART1 is
 * configured for 31.25 kbps operation using its built-in baud-rate generator.
 * The optoisolator is required on the receive port, so some external hardware
 * is necessary.
 *
 * The functions for handling the UART MIDI messages are in midi_uart.c/h.
 *
 * For MIDI IN, the serial receive port stuffs everything that arrives into a
 * FIFO. The main loop calls MIDIUART_readMessage() repeatedly. Each time that
 * function is called, the receive FIFO is popped and new bytes are parsed by
 * a state machine. If the FIFO is empty or is emptied before all bytes of a message
 * are received, the function returns FALSE. The next call(s) will eventually
 * complete reception of the entire message. If a complete message is received,
 * the function returns TRUE (and there may be more bytes in the FIFO, but they
 * are handled on the next call).
 * Since this example doesn't do anything on the board with the received packets,
 * the main loop then just writes them to the host with USBD_Write().
 *
 * For MIDI OUT, the only source for messages is the USB on Cable Number 1. Every
 * time through the main loop, the USB MIDI input message FIFO is popped and the
 * header of the new message is inspected. If the Cable Number indicates that the
 * message is intended for the hardware port, the data bytes in the message are
 * put into a buffer for writing to the serial transmitter. The header is parsed
 * to find out how many bytes of the message need are to be sent. That buffer is
 * written to the MIDI UART FIFO. If there is room in that FIFO for more messages,
 * the BULK OUT endpoint is re-armed with a call to USBD_Read().
 *
 * Note that if there is no room in the serial transmitter's FIFO for another
 * message, messages intended for the board (the virtual cable) are still blocked
 * until that FIFO has space. This is because we cannot know in advance whether
 * new messages are intended for the UART or the board. In practice this should
 * not be an issue. (Famous last words.)
 **************************************************************************
 * The LEDs on the board are controlled both by buttons and the joystick as well
 * as via MIDI message from the host over USB. This is just to demonstrate how
 * this can be done.
 *
 **************************************************************************
 * This code uses the SiLabs EFM8UB2 peripheral drivers for ADC0, UART1 and USB0.
 * It uses the EFM8_USB library.
 * It uses BSP drivers for the joystick and the LED.
 * The button and joystick handlers were combined into source joybutton.c/h.
 * As the joystick uses the ADC, the ISR for the ADC-convert-done handler is in
 * the joybutton.c source.
 * Timer 5 is used to pace the A/D conversions.
 **************************************************************************
 *
 * EFM8 RESOURCE USAGE.
 *
 * ADC_0:
 * SAR Clock Divider = 0x05
 * Right-justified data
 * Conversion starts on overflow of Timer 5.
 * Analog input on P0.4, other input to ADC is ground.
 * Voltage reference is VDD.
 *
 * HFOSC_0:
 * SYSCLK is HFOSC / 1.
 * HFOSC is used as SYSCLK and USBCLK.
 *
 * INTERRUPTS.
 * ADINT enabled.
 * USBINT enabled.
 * UART1 Interrupts enabled.
 *
 * CROSSBAR is enabled.
 * Weak pullups enabled.
 * CEX0, CEX1, CEX2 routed to pins.
 * UART1 TX, RX routed to pins.
 *
 * PORTS: See InitDevice.c.
 *
 * PCA_0 enabled.
 * Uses SYSCLK.
 * Watchdog disabled.
 * PCACH_0 enabled, set as 8-bit PWM output on CEX0, used for LED.
 * PCACH_1 enabled, set as 8-bit PWM output on CEX1, used for LED.
 * PCACH_2 enabled, set as 8-bit PWM output on CEX2, used for LED.
 *
 * TIMER_5 enabled.
 * Used to start A/D conversions at maximum sample rate.
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
 * Global buffer for the USB OUT endpoint.
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
}

/**
 * main() Routine
 */
int main(void) {
	USBMIDI_Message_t xdata	uimep;		//!< user interface MIDI events we write to the host
	USBMIDI_Message_t xdata	spmep;		//!< events received on serial MIDI in we write to the host
	USBMIDI_Message_t xdata	usbmep;		//!< events received from USB endpoint
	uint8_t xdata	MsgToUart[3];		//!< MIDI messages we write to the serial transmitter
	uint8_t xdata	MsgToUartSize;		//!< how many bytes in that message?
	joybuttonReport_t xdata	jbr;		//!< Report indicating state of joystick and buttons.
	bit LBState;		//!< the left button's immediate state, for toggle test
	bit RBState;		//!< the right button's immediate state, for toggle test
	bit CBState;//!< joystick center button's immediate state, for toggle test
	bool roomInTxFifo;					//!< from call to MIDIUART_writeMessage()
	Color xdata	ledcolor;				//!< The color of the RGB LED

	// Call hardware initialization routine
	enter_DefaultMode_from_RESET();

	// we don't use the display.
	BSP_DISP_EN = 0;

	// Initialize some other stuff.
	LBState = 0;
	RBState = 0;
	CBState = 0;
	roomInTxFifo = true;		// yes, there is, at the start of time

	// Clear the endpoint buffer, mainly for debug.
	// Use MsgToUartSize as the iterator so we don't have to declare another automatic.
	for (MsgToUartSize = 0; MsgToUartSize < SLAB_USB_EP1OUT_MAX_PACKET_SIZE;
			MsgToUartSize++) {
		EndpointBuffer[MsgToUartSize] = 0;
	}

	// Clear the MIDI events received from the USB endpoint, mainly for debug.
	usbmep.header = 0x00;
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
		JOYBUTTON_GetReport (&jbr);

		/*
		 * for now, if a button was pressed or the joystick was moved,
		 * send a Control Change message MIDI channel 1, and also do something
		 * fun to the RGB LED.
		 */
		if (jbr.Button == LEFT_BUTTON) {
			uimep.header = USB_MIDI_HEADER(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE); // CC on channel 1
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
			while (USBD_EpIsBusy (EP1IN))
				;
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
		} // Left Button

		if (jbr.Button == RIGHT_BUTTON) {
			uimep.header = USB_MIDI_HEADER(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE);
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
			while (USBD_EpIsBusy (EP1IN))
				;
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
		} // Right Button

		if (jbr.Button == CENTER_BUTTON) {
			uimep.header = USB_MIDI_HEADER(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE);
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
			while (USBD_EpIsBusy (EP1IN))
				;
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
		} // Center Button

		if (jbr.X) {
			ledcolor.red = 0x00;
			ledcolor.green = 0x00;
			uimep.header = USB_MIDI_HEADER(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE);
			uimep.byte1 = MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0); // CC on channel 1
			uimep.byte2 = 83;
			uimep.byte3 = jbr.X;
			ledcolor.blue = jbr.X;
			RGB_SetColor(ledcolor, 255);
			while (USBD_EpIsBusy (EP1IN))
				;
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
		} // Joystick X

		if (jbr.Y) {
			ledcolor.red = 0x00;
			ledcolor.green = 0x00;
			uimep.header = USB_MIDI_HEADER(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE);
			uimep.byte1 = MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0); // CC on channel 1
			uimep.byte2 = 84;
			uimep.byte3 = jbr.Y;
			ledcolor.blue = jbr.Y;
			RGB_SetColor(ledcolor, 255);
			while (USBD_EpIsBusy (EP1IN))
				;
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
		} // Joystick Y

		/*
		 * Pop the USB MIDI message stack for the next event message and parse it.
		 * The MIDI cable number whether it should be sent on to the serial MIDI
		 * port, or whether it stays on board (to control LEDs).
		 * If the cable number is neither of those, the packet is dropped on
		 * the floor.
		 */
		if (USBMIDIFIFO_Pop (&usbmep)) {
			// if it targets the hardware port, just pass it along.
			// We don't care much about the particular event, just the port (Cable Number).
			// the buffer is only three bytes because the USB packet can only give us
			// up to three bytes at a time.
			if (USB_MIDI_CABLE_NUMBER(usbmep.header) == UART_CN) {
				MsgToUart[0] = usbmep.byte1;
				MsgToUart[1] = usbmep.byte2;
				MsgToUart[2] = usbmep.byte3;

				switch (USB_MIDI_CODE_INDEX_NUMBER(usbmep.header)) {
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

			} else if (USB_MIDI_CABLE_NUMBER(usbmep.header) == VIRTUAL_CN) {
				if (usbmep.byte1 == MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0)) {
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
			USBD_Read(EP1OUT, &EndpointBuffer, SLAB_USB_EP1OUT_MAX_PACKET_SIZE,
					true);
		}

		/*
		 * Handle messages received on the hardware IN port.
		 * These get packetized by the serial receiver into the proper USB MIDI
		 * message format for sending to host on USB IN endpoint.
		 * We just pass along the packet.
		 */
		if (MIDIUART_readMessage (&spmep)) {
			while (USBD_EpIsBusy (EP1IN))
				;
			USBD_Write(EP1IN, (uint8_t *) &spmep, sizeof(spmep), false);
		}

	} // main while(1) loop
} // main()
