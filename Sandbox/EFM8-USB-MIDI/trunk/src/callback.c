/*******************************************************************************
 * @file callback.c
 * @brief USB Callbacks.
 *******************************************************************************/

//=============================================================================
// src/callback.c: generated by Hardware Configurator
//
// This file is only generated if it does not exist. Modifications in this file
// will persist even if Configurator generates code. To refresh this file,
// you must first delete it and then regenerate code.
//=============================================================================
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8UB2_Register_Enums.h>
#include <efm8_usb.h>
#include "usb_midi.h"

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
#if USE_SLAB_EP1OUT_HANDLER == 0
extern SI_SEGMENT_VARIABLE(EndpointBuffer, MIDI_Event_Packet_t, SI_SEG_IDATA);
#else
extern SI_SEGMENT_VARIABLE(EndpointBuffer[SLAB_USB_EP1OUT_MAX_PACKET_SIZE], uint8_t, SI_SEG_IDATA);
#endif
//---------------------------------	--------------------------------------------
// Functions
//-----------------------------------------------------------------------------

#if SLAB_USB_SOF_CB
void USBD_SofCb(uint16_t sofNr) {
	UNREFERENCED_ARGUMENT(sofNr);
}
#endif

/*
 * When state changes to connected, arm the endpoint and enable the callback.
 * I don't think there's a way to cancel this.
 */
void USBD_DeviceStateChangeCb(USBD_State_TypeDef oldState,
                              USBD_State_TypeDef newState) {
	if (newState == USBD_STATE_CONFIGURED) {
#if USE_SLAB_EP1OUT_HANDLER == 0
		USBD_Read(EP1OUT, (uint8_t *) &EndpointBuffer, sizeof(MIDI_Event_Packet_t), // midi messages are four bytes
				false); // callback not implemented.
#else
		USBD_Read(EP1OUT, &EndpointBuffer, SLAB_USB_EP1OUT_MAX_PACKET_SIZE, // midi messages are four bytes
		true); // use callback to move data from endpoint to MIDI FIFO.
#endif

	}
}

/*
 * In the callback, read four bytes from the endpoint buffer into a MIDI message
 * packet and then push that packet into the MIDI data FIFO.
 * We are going to assume that we have multiple-of-four bytes in the endpoint buffer.
 */
uint16_t USBD_XferCompleteCb(uint8_t epAddr, USB_Status_TypeDef status,
		uint16_t xferred, uint16_t remaining) {


#if USE_SLAB_EP1OUT_HANDLER == 1
	MIDI_Event_Packet_t mep;
	uint8_t *epb;
	epb = EndpointBuffer;
	while (xferred) {
		mep.event = *epb++;
		mep.byte1 = *epb++;
		mep.byte2 = *epb++;
		mep.byte3 = *epb++;
		MIDIFIFO_Push(&mep);
		xferred -= 4;
	}
	USBD_Read(EP1OUT, &EndpointBuffer, SLAB_USB_EP1OUT_MAX_PACKET_SIZE, // midi messages are four bytes
			true); // use callback to move data from endpoint to MIDI FIFO.
#else
	UNREFERENCED_ARGUMENT(xferred);
#endif
	UNREFERENCED_ARGUMENT(epAddr);
	UNREFERENCED_ARGUMENT(status);
	UNREFERENCED_ARGUMENT(remaining);

	// always return zero for bulk endpoints.
	return 0;
} // XferCompleteCb
