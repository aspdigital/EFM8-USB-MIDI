General concept of how this works.

** MIDI IN, to host computer over BULK IN Endpoint. **
Any time there is an event that requires data to be sent back to the host, we call USBD_Write()
with a MIDI_Event_Packet_t as the data buffer and the count set to 4, the size of that packet.
Callback is set false, as we don't care.


** MIDI OUT, from host computer to USB device over bulk endpoint **
After the device configures and such, we have to "prime the pump" and call USBD_Read() with
a MIDI_Event_Packet_t as the data buffer and the count set to 4. The callback should be set
to true.
Then when a packet arrives, the callback is triggered. In the callback, we copy the buffer
to a global variable of MIDI_Event_Packet_t and set a global "got new packet" flag. We then call
USBD_Read() again, with the original packet passed as the buffer. This is basically double-buffering.

 