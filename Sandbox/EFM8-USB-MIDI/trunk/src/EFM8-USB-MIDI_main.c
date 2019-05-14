//=========================================================
// src/EFM8-USB-MIDI_main.c: generated by Hardware Configurator
//
// This file will be updated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!!
//=========================================================

/*
 * NOTES!
 *
 * MIDI ports are the hardware or virtual connections.
 * This design has two in and two out ports.
 * Port 0 is the virtual port we use to control the hardware (for IN) and send back
 * 	button-and-knob changes.
 * Port 1 is the physical port connected to UART1.
 */

/*
 * Handling physical-port access. This uses the SiLab's Uart1 driver, and this
 * should probably be changed to something more general.
 *
 * USB MIDI OUT messages for port 1 are routed to UART1 for transmit.
 * The event part of the messages is stripped off and the three data bytes are
 * loaded into the UART's transmit buffer. The callback exists but isn't used
 * because it's not necessary.
 *
 * Messages received on physical port 1 in have an event byte added and a USB
 * MIDI message is built from what was received, and that message is written
 * to the MIDI bulk IN endpoint.
 */

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8UB2_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
// $[Generated Includes]
#include "efm8_usb.h"
// [Generated Includes]$
#include "rgb_led.h"
#include "bsp.h"
#include "disp.h"
#include "render.h"
#include "tick.h"
#include "joybutton.h"
#include "midi.h"
#include "usb_midi.h"
#include "midi_uart.h"

/*
 * Global buffers for the OUT endpoint.
 * One buffer is used for the USBD_Read() and the callback.
 * The other buffer is used for parsing the message. The contents of the
 * first buffer are copied into it in the transfer-complete callback.
 */

#if USE_SLAB_EP1OUT_HANDLER == 0
extern SI_SEGMENT_VARIABLE(EndpointBuffer, MIDI_Event_Packet_t, SI_SEG_IDATA);
#else
extern SI_SEGMENT_VARIABLE(EndpointBuffer[SLAB_USB_EP1OUT_MAX_PACKET_SIZE], uint8_t, SI_SEG_IDATA);
#endif

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

#if 0
/* UART callbacks. UART1 is for the MIDI port. Perhaps this should be in a midi directory? */
void UART1_transmitCompleteCb(void) {

}

void UART1_receiveCompleteCb(void) {

}
#endif

/*
 * Structure which holds joystick and button-press information.
 * Yes, it's an HID report structure.
 */
struct joystickReportData {
	uint8_t Button; /**< Button mask for currently pressed buttons in the game pad. */
	uint8_t X;
	uint8_t Y;
} joystickReportData;

//-----------------------------------------------------------------------------
// CreateJoystickReport() Routine
// ----------------------------------------------------------------------------
//
// Description - Generate joystick status report according Joystick and Button
//               status.
//
//-----------------------------------------------------------------------------
void CreateJoystickReport(void) {
	uint8_t joyStatus = Joystick_GetStatus();

	memset(&joystickReportData, 0, sizeof(joystickReportData));

	if (joyStatus & JOY_UP) {
		joystickReportData.Y = 0x7F;
	} else if (joyStatus & JOY_DOWN) {
		joystickReportData.Y = 0x01;
	}

	if (joyStatus & JOY_LEFT) {
		joystickReportData.X = 0x01;
	} else if (joyStatus & JOY_RIGHT) {
		joystickReportData.X = 0x7F;
	}

	joystickReportData.Button = joyStatus & BUTTON_MASK;
}

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main(void) {
//	static SI_SEGMENT_VARIABLE(line[DISP_BUF_SIZE], uint8_t, RENDER_LINE_SEG);
//	uint8_t y;
//	uint16_t lastTick;
	MIDI_Event_Packet_t uimep;		// user interface MIDI events we write to the host
	MIDI_Event_Packet_t spmep;		// events received on serial MIDI in we write to the host
	MIDI_Event_Packet_t usbmep;		// events received from USB endpoint
	uint8_t MsgToUart[3];			// MIDI messages we write to the serial transmitter
	uint8_t MsgToUartSize;			// how many bytes in that message?
	bit LBState;
	bit RBState;
	bool usbIntsEnabled;

	// Call hardware initialization routine
	enter_DefaultMode_from_RESET();
#if 0
	DISP_Init();
	lastTick = GetTickCount();

	for (y = 0; y < FONT_HEIGHT; y++) {
		RENDER_ClrLine (line);
		RENDER_StrLine(line, 3, y, "TEST");
		DISP_WriteLine(4 + y, line);
	}
#endif

	LBState = 0;
	RBState = 0;

#if USE_SLAB_EP1OUT_HANDLER == 0
	EndpointBuffer.event = 0x00;
	EndpointBuffer.byte1 = 0x00;
	EndpointBuffer.byte2 = 0x00;
	EndpointBuffer.byte3 = 0x00;
#else
	for (MsgToUartSize = 0; MsgToUartSize < SLAB_USB_EP1OUT_MAX_PACKET_SIZE; MsgToUartSize++) {
		EndpointBuffer[MsgToUartSize] = 0;
	}
#endif
	usbmep.event = 0x00;
	usbmep.byte1 = 0x00;
	usbmep.byte2 = 0x00;
	usbmep.byte3 = 0x00;

	MIDIUART_init();
	MIDIFIFO_Init();

	// this is brute force.
	// for now, no point in going further until USB connects.
	while (USBD_GetUsbState() != USBD_STATE_CONFIGURED)
		;

	// start timer for joystick.
	MsgToUartSize = SFRPAGE;
	SFRPAGE = CONFIG_PAGE;
	TMR5CN0_TR5 = 1;
	SFRPAGE = MsgToUartSize;

	while (1) {
// $[Generated Run-time code]
// [Generated Run-time code]$
#if 0
		for (y = 0; y < FONT_HEIGHT; y++) {
			RENDER_ClrLine (line);
			RENDER_StrLine(line, 3, y, "TEST");
			DISP_WriteLine(4 + y, line);
		}
#endif
		// check the joystick and buttons for changes.
		CreateJoystickReport();

		// for now, if a button was pressed, send a Control Change message on MIDI channel 1.
		if (joystickReportData.Button == LEFT_BUTTON) {
			uimep.event = USB_MIDI_EVENT(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE); // CC on channel 1
			uimep.byte1 = MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0); // CC on channel 1
			uimep.byte2 = 80;
			RGB_CEX_BLUE = 0x00;
			RGB_CEX_GREEN = 0x00;
			if (LBState == 0) {
				RGB_CEX_RED = 0x7F;
				uimep.byte3 = 0x7F;		// full
			} else {
				RGB_CEX_RED = 0x00;
				uimep.byte3 = 0x00;
			}
			LBState = !LBState;
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Left Button

		if (joystickReportData.Button == RIGHT_BUTTON) {
			uimep.event = USB_MIDI_EVENT(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE);
			uimep.byte1 = MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0); // CC on channel 1
			uimep.byte2 = 81;
			RGB_CEX_BLUE = 0x00;
			RGB_CEX_RED = 0x00;
			if (RBState == 0) {
				RGB_CEX_GREEN = 0x7F;
				uimep.byte3 = 0x7F;		// full
			} else {
				RGB_CEX_GREEN = 0x00;
				uimep.byte3 = 0x00;
			}
			RBState = !RBState;
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Right Button

		if (joystickReportData.X) {
			RGB_CEX_RED = 0x00;
			RGB_CEX_GREEN = 0x00;
			uimep.event = USB_MIDI_EVENT(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE);
			uimep.byte1 = MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0); // CC on channel 1
			uimep.byte2 = 82;
			uimep.byte3 = joystickReportData.X;
			RGB_CEX_BLUE = joystickReportData.X;
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Joystick X

		if (joystickReportData.Y) {
			RGB_CEX_RED = 0x00;
			RGB_CEX_GREEN = 0x00;
			uimep.event = USB_MIDI_EVENT(VIRTUAL_CN, USB_MIDI_CIN_CTRLCHANGE);
			uimep.byte1 = MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0); // CC on channel 1
			uimep.byte2 = 83;
			uimep.byte3 = joystickReportData.Y;
			RGB_CEX_BLUE = joystickReportData.Y;
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &uimep, sizeof(uimep), false);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Joystick X

		/*
		 * Pop the MIDI message stack for the next event message and parse it.
		 */
		// did we get a new event?
		if (MIDIFIFO_Pop(&usbmep)) {
			P3_B3 = 1;
//			usbIntsEnabled = USB_GetIntsEnabled();
//			USB_DisableInts();
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

//				P3_B0 = 1;
				MIDIUART_writeMessage(MsgToUart, MsgToUartSize);
//				P3_B0 = 0;

			} else if (USB_MIDI_CABLE_NUMBER(usbmep.event)
					== VIRTUAL_CN) {

				if (usbmep.byte1
						== MIDI_STATUS_BYTE(MIDI_MSG_CTRLCHANGE, 0)) {
					switch (usbmep.byte2) {
					case 80: // left button
						RGB_CEX_GREEN = usbmep.byte3 << 1;
						RGB_CEX_RED = 0;
						RGB_CEX_BLUE = 0;
						break;
					case 81: // right button
						RGB_CEX_GREEN = 0;
						RGB_CEX_RED = usbmep.byte3 << 1;
						RGB_CEX_BLUE = 0;
						break;
					case 82: // joystick X
						RGB_CEX_GREEN = 0;
						RGB_CEX_RED = 0;
						RGB_CEX_BLUE = usbmep.byte3 << 1;
						break;
					case 83: // joystick Y
						RGB_CEX_GREEN = 0; //midiInMsg.byte3 << 1;
						RGB_CEX_RED = 0;
						RGB_CEX_BLUE = usbmep.byte3 << 1;
						break;
					} // switch
				} // event
			} // which cable number?
//			if (usbIntsEnabled)
//				USB_EnableInts();

			P3_B3 = 0;
		} // if there's a message in the FIFO

		/*
		 * Handle messages received on the hardware IN port.
		 * These get packetized by the serial receiver for sending to host on USB IN endpoint.
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
