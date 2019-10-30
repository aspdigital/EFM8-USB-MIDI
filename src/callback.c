/**
 * @file callback.c
 * @brief USB Callbacks.
 *
 * We use two of the callbacks in this project.
 *
 * DeviceStateChange is invoked when the device connects (or disconnects) from
 * the host. We care about when it connects. When that happens, we will prime
 * the USB OUT handler on Endpoint 1 with a buffer in the call to USBD_Read().
 *
 * XferComplete is invoked when any endpoint's transfer has completed. We check
 * to see that it is our OUT ENDPOINT 1 and if so, we push received MIDI
 * messages to our FIFO.
 *
 * Modified:
 * 2019-05-23 andy. Better header, clean up.
 * 2019-10-30 andy. No need to prime the USB OUT endpoint pump with USBD_Read()
 * 	here -- the first call in the main loop is sufficient.
 */

#include <efm8_usb.h>
#include "usb_midi.h"

/**
 * In the interrupt handler, we read the endpoint FIFO into this buffer.
 * It holds exactly one MIDI message.
 * This buffer's contents will be pushed to the MIDI message FIFO immediately.
 * This is externed in main(), which uses it to in calls to USBD_Read().
 */
SI_SEGMENT_VARIABLE(EndpointBuffer[SLAB_USB_EP1OUT_MAX_PACKET_SIZE], uint8_t, SI_SEG_IDATA);

#if SLAB_USB_SOF_CB
void USBD_SofCb(uint16_t sofNr) {
	UNREFERENCED_ARGUMENT(sofNr);
}
#endif

/**
 * When state changes to connected, arm the endpoint and enable the callback.
 * @param[in] oldState is not used.
 * @param[in] newState is checked, if we are configured, we'll set up a buffer for
 * 	OUT endpoints.
 */
void USBD_DeviceStateChangeCb(USBD_State_TypeDef oldState,
                              USBD_State_TypeDef newState) {
/*
	UNREFERENCED_ARGUMENT(oldState);
	if (newState == USBD_STATE_CONFIGURED) {
		USBD_Read(EP1OUT,
				&EndpointBuffer,
				SLAB_USB_EP1OUT_MAX_PACKET_SIZE,
				true);
	}
*/
} // USBD_DeviceStateChangeCb()

/**
 * Transfer-complete callback, invoked by the various endpoint interrupt handlers.
 *
 * In the callback, read four bytes from the endpoint buffer into a MIDI message
 * packet and then push that packet into the MIDI data FIFO.
 * We are going to assume that we have multiple-of-four bytes in the endpoint buffer.
 * Endpoint is re-armed in main() after it determines there is space in various
 * buffers to handle another packet.
 * @param[in] epAddr: the endpoint for which this callback was invoked.
 * @param[in] status: transfer status. If not OK, we have problems.
 * @param[in] xferred: how many bytes are in our endpoint buffer.
 * @param[in] remaining: # of bytes left to receive from this endpoint.
 * @return 0 for bulk endpoints.
 */
uint16_t USBD_XferCompleteCb(uint8_t epAddr, USB_Status_TypeDef status,
		uint16_t xferred, uint16_t remaining) {

	USBMIDI_Message_t xdata mep;
	uint8_t *epb;

	UNREFERENCED_ARGUMENT(remaining);

	if ((epAddr == EP1OUT) && (status == USB_STATUS_OK))
	{
		epb = EndpointBuffer;
		while (xferred) {
			mep.header = *epb++;
			mep.byte1 = *epb++;
			mep.byte2 = *epb++;
			mep.byte3 = *epb++;
			USBMIDIFIFO_Push(&mep);
			xferred -= 4;
		}
	}

	// always return zero for bulk endpoints.
	return 0;
} // XferCompleteCb
