General concept of how this works.

** MIDI IN, to host computer over BULK IN Endpoint. **
Any time there is an event that requires data to be sent back to the host, we call USBD_Write()
with a MIDI_Event_Packet_t as the data buffer and the count set to 4, the size of that packet.
Callback is set false, as we don't care. Prior to calling USBD_Write(), we check to see if the 
endpoint is already busy, and wait for it to not be so.


** MIDI OUT, from host computer to USB device over bulk out endpoint ** 

OUT EP1 has its max packet size set to 32. This means that up to eight MIDI messages (4 bytes each)
can be sent from the host in a packet. In some cases only one message is sent. This
needs to be handled. One way to handle this would be to push all incoming MIDI messages into
a software FIFO (akin to the UART FIFOs). Perhaps the FIFO needs to store only, say, 
4 messages or 16 bytes? 

After the device configures and such, we have to "prime the pump" and call USBD_Read() with
an eight-byte buffer as the data buffer and the count set to 4. The callback should be set
to true. This is how we can handle one MIDI message or two in the USB OUT packet.

After the USB hardware receives a packet, it interrupts. The handler will check to
see how many bytes were received. This will be either four or eight. Therefore,
one or two MIDI messages will be pushed onto the message FIFO.

 The main loop will test to see if there are messages in the FIFO and pop one at
 a time. The message will be parsed to see if it is intended for the hardware port
 or for controlling something on the board (LED, whatever).