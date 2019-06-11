/**
 * \file midi_uart.h
 *
 *  Created on: Apr 20, 2019
 *      Author: andy
 *
 * This module handles writing to the MIDI OUT port and reading from the MIDI IN port when
 * the EFM8 UART1 is the transport. This assumes that the port has already been configured.
 *
 * Included here is the UART's ISR.
 *
 * For MIDI OUT, we present a MIDIUART_writeMessage() function, which takes as its arguments a pointer
 * to a MIDI message packet and the packet size. The function writes the packet to the UART's outgoing
 * FIFO. This will block until the contents of the message are successfully written to the FIFO.
 *
 * It is assumed that the source of the MIDI OUT message is the USB MIDI OUT function. That
 * function receives a four byte packet, the first of which is the event byte indicating cable number
 * (cable and port are synonymous) and a code indicating the contents of the other three bytes.
 * So other code will take that MIDI message, determine if it intended for the UART Out Port
 * and how many bytes in the message it needs to send, and it reformats them into an outgoing
 * package with the required number of bytes.
 *
 * For MIDI IN, we present a MIDIUART_readMessage() function, which takes as its argument a pointer
 * to a MIDI message package. The function will return the oldest packet in the FIFO in that argument,
 * and the function's return value will be the size of the packet.
 * If there are no packets, the function returns 0 and the message argument is not valid.
 *
 * Reading is always trickier than writing. Because the message from the UART needs to
 * be repackaged into a four-byte packet for USB, the readMessage logic needs to be
 * clever. As bytes come in, they are inspected to see if they are Status (value 0x80 or greater)
 * or Data bytes. Status bytes are decoded to determine how many data bytes will follow it.
 * For most messages this is straightforward as their packet sizes are defined.
 * SysEx is the exception, as we don't know how many data bytes it may use. But we know
 * these messages are framed by 0xF0 for SOX (Start of SysEx) and 0xF7 (EOX).
 * So when we pop the FIFO and see 0xF0, we pop the next 1, 2, 3 or 4 bytes.
 * If none are 0xF7, we create a message packet with CIN 0x4 and the packet has the
 * first three bytes.
 * If byte 4 is 0xF7 we send CIN 0x7 (SysEx Ends with following three bytes).
 * If byte 3 is 0xF7 we send CIN 0x6
 * and so forth.
 *
 */

#ifndef MIDI_UART_H_
#define MIDI_UART_H_

#include <SI_EFM8UB2_Register_Enums.h>
#include "midi.h"

/**
 * Define the MIDI UART FIFO size.
 * This applies to both transmit and receive FIFOs.
 */
#ifndef MIDI_UART_FIFO_SIZE
#define MIDI_UART_FIFO_SIZE (128)
#endif

/**
 * Clear the FIFOs and all.
 * This should probably wrap up everything needed to configure the UART for this application.
 */
void MIDIUART_init(void);

/**
 * Write the given message to the UART's transmit FIFO.
 * We don't have to be concerned that the FIFO will overflow, as we'll hold off
 * USB OUT transactions if there isn't enough space here.
 * We return TRUE if there _is_ space in the FIFO for another USB OUT packet's
 * worth of messages.
 *
 * @param[in]  msg		Pointer to an array of bytes that comprise a MIDI message.
 * @param[in]  msize	The number of bytes in that message.
 */
void MIDIUART_writeMessage(uint8_t xdata *msg, uint8_t msize);

/**
 * Check to see if there is enough room in the MIDI UART's transmit FIFO to
 * accept an endpoint packet's worth of message bytes.
 * @return true if that's the case.
 */
bool MIDIUART_isRoomInFifo(void);

/**
 * Read bytes from the serial port receive FIFO and assemble them into a proper
 * USB MIDI four-byte message packet.
 * It reads however many bytes are in that FIFO. Depending on serial port traffic,
 * more than one call may be required to complete a message.
 * It returns true when a message has been fully assembled.
 *
 * @param[in,out] msg 	The assembled USB-MIDI message packet is returned here.
 * @return True when msg contains an entire USB-MIDI message packet.
 */
bool MIDIUART_readMessage(USBMIDI_Message_t xdata *msg);

#endif /* MIDI_UART_H_ */
