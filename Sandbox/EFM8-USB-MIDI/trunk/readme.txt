General concept of how this works.

For both directions we have FIFO buffers that store MIDI message packets. The
FIFOs are larger than the max packet size for Bulk endpoints, so we have some
flexibility. Therefore there are 20 entries in the FIFOs, or 80 bytes. Since
the packets differentiate the virtual MIDI cable number, both ports feed the
FIFO and pull from it.

** MIDI IN, to host computer over BULK IN Endpoint. **
Any time there is an event that results in sending a message to the host, the
userland code writes to the MIDI IN message FIFO. Then at SOF, we set a flag, 
which when read in userland indicates that we should send the oldest 16 messages
to the host. 

** MIDI OUT, from host computer to USB device over bulk endpoint **

 