//=========================================================
// src/EFM8-USB-MIDI_main.c: generated by Hardware Configurator
//
// This file will be updated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!!
//=========================================================

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
#include "usb_midi.h"

/*
 * Global buffer for the OUT endpoint.
 */
SI_SEGMENT_VARIABLE(midiInMsg, MIDI_Event_Packet_t, SI_SEG_XDATA);
// flag indicating a new event.
bit newInEvent;

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

/* UART callbacks. UART1 is for the MIDI port. Perhaps this should be in a midi directory? */
void UART1_transmitCompleteCb(void) {

}

void UART1_receiveCompleteCb(void) {

}

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
	MIDI_Event_Packet_t mep;
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
	newInEvent = 0;

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

		// for now, if a button was pressed, send a Control Change message on MIDI channel 3.
		if (joystickReportData.Button == LEFT_BUTTON) {
			mep.event = 0x0B;		// CC on channel 1
			mep.byte1 = 0xB0;
			mep.byte2 = 80;
			RGB_CEX_BLUE = 0x00;
			RGB_CEX_GREEN = 0x00;
			if (LBState == 0) {
				RGB_CEX_RED = 0x7F;
				mep.byte3 = 0x7F;		// full
			} else {
				RGB_CEX_RED = 0x00;
				mep.byte3 = 0x00;
			}
			LBState = !LBState;
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &mep, sizeof(mep), true);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Left Button

		if (joystickReportData.Button == RIGHT_BUTTON) {
			mep.event = 0x0B;		// CC on channel 1
			mep.byte1 = 0xB0;		// CC on channel 1
			mep.byte2 = 81;
			RGB_CEX_BLUE = 0x00;
			RGB_CEX_RED = 0x00;
			if (RBState == 0) {
				RGB_CEX_GREEN = 0x7F;
				mep.byte3 = 0x7F;		// full
			} else {
				RGB_CEX_GREEN = 0x00;
				mep.byte3 = 0x00;
			}
			RBState = !RBState;
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &mep, sizeof(mep), true);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Right Button

		if (joystickReportData.X) {
			RGB_CEX_RED = 0x00;
			RGB_CEX_GREEN = 0x00;
			mep.event = 0x0B;		// CC on channel 1
			mep.byte1 = 0xB0;		// CC on channel 1
			mep.byte2 = 82;
			mep.byte3 = joystickReportData.X;
			RGB_CEX_BLUE = joystickReportData.X;
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &mep, sizeof(mep), true);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Joystick X

		if (joystickReportData.Y) {
			RGB_CEX_RED = 0x00;
			RGB_CEX_GREEN = 0x00;
			mep.event = 0x0B;		// CC on channel 1
			mep.byte1 = 0xB0;		// CC on channel 1
			mep.byte2 = 83;
			mep.byte3 = joystickReportData.Y;
			RGB_CEX_BLUE = joystickReportData.Y;
			usbIntsEnabled = USB_GetIntsEnabled();
			USB_DisableInts();
			USBD_Write(EP1IN, (uint8_t *) &mep, sizeof(mep), true);
			if (usbIntsEnabled)
				USB_EnableInts();
		} // Joystick X
#if 1
		// Try to read from the OUT endpoint.
		if (!USBD_EpIsBusy(EP1OUT)) {
			USBD_Read(EP1OUT, (uint8_t *) &midiInMsg,
					sizeof(MIDI_Event_Packet_t), // midi messages are four bytes
					true);
		}

		// did we get a new event?
		if (newInEvent) {
			newInEvent = 0;
			if (midiInMsg.byte1 == 0xB0) {
				switch (midiInMsg.byte2) {
				case 80: // left button
					RGB_CEX_GREEN = midiInMsg.byte3 << 1;
					RGB_CEX_RED = 0;
					RGB_CEX_BLUE = 0;
					break;
				case 81: // right button
					RGB_CEX_GREEN = 0;
					RGB_CEX_RED = midiInMsg.byte3 << 1;
					RGB_CEX_BLUE = 0;
					break;
				case 82: // joystick X
					RGB_CEX_GREEN = 0;
					RGB_CEX_RED = 0;
					RGB_CEX_BLUE = midiInMsg.byte3 << 1;
					break;
				case 83: // joystick Y
					RGB_CEX_GREEN = 0; //midiInMsg.byte3 << 1;
					RGB_CEX_RED = 0;
					RGB_CEX_BLUE = midiInMsg.byte3 << 1;
					break;
				} // switch
			} // event
		} // newInEvent
#endif

	} // main while(1) loop
} // main()
