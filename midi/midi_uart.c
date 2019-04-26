/*
 * midi_uart.c
 *
 *  Created on: Apr 20, 2019
 *      Author: andy
 */
#include <SI_EFM8UB2_Register_Enums.h>
#include "bsp_config.h"
#include "midi.h"
#include "usb_midi.h"
#include "midi_uart.h"

/*
 * Define a software FIFO for the UART. We need pointers and a buffer.
 * The buffer is defined outside of the structure so we can put it in
 * XDATA space while the pointers are in DATA space.
 */
typedef struct {
	uint8_t head;						/*!< Index of the head of the FIFO */
	uint8_t tail;						/*!< Index of the tail of the FIFO */
	uint8_t count;						/*!< Number of bytes in the FIFO */
} fifoptr_t;

static data fifoptr_t rxfifoptr;
static xdata uint8_t rxfifobuf[MIDI_UART_FIFO_SIZE];
static data fifoptr_t txfifoptr;
static xdata uint8_t txfifobuf[MIDI_UART_FIFO_SIZE];
static bit txidle;	// indicates whether a new packet write needs to kick off transmit.

/*
 * UART ISR.
 *
 * Transmitter:
 * After clearing the interrupt bit, check to see if there is more to send, and if so, pop
 * the FIFO and load the new byte into SBUF1 for transmit. If not, set the txidle bit so
 * future FIFO loads know to kick off the transmission.
 *
 * Receiver.
 * After clearing the interrupt bit, stuff the incoming byte into the receive FIFO.
 */
SI_INTERRUPT (UART1_ISR, UART1_IRQn)
{
	if (SCON1 & SCON1_TI__BMASK) {
		SCON1 &= ~SCON1_TI__BMASK;

		if (txfifoptr.count) {
			SBUF1 = txfifobuf[txfifoptr.tail];
			txfifoptr.tail++;
			if (txfifoptr.tail >= MIDI_UART_FIFO_SIZE) {
				txfifoptr.tail = 0;
			}
			txfifoptr.count--;
			txidle = 0;
		} else {
			txidle = 1;
		}
	} // transmit interrupt.

	if (SCON1 & SCON1_RI__BMASK) {
		SCON1 &= ~SCON1_RI__BMASK;
		rxfifobuf[rxfifoptr.head] = SBUF1;
		rxfifoptr.head++;
		if (rxfifoptr.head >= MIDI_UART_FIFO_SIZE) {
			rxfifoptr.head = 0;
		}
		rxfifoptr.count++;
	} // receive interrupt
} // UART1_ISR

/*
 * Pop the receive FIFO. This will not be called if the FIFO is empty.
 */
static uint8_t MIDIUART_rxFifoPop(void) {
	uint8_t c;

	c = rxfifobuf[rxfifoptr.tail];
	rxfifoptr.tail++;
	if (rxfifoptr.tail >= MIDI_UART_FIFO_SIZE) {
		rxfifoptr.tail = 0;
	}
	rxfifoptr.count--;
	return c;
} // MIDIUART_rxFifoPop

/*
 * Peek at the next thing in the receive FIFO but don't pop it off.
 */
static uint8_t MIDIUART_rxFifoPeek(void) {
	return rxfifobuf[rxfifoptr.tail];
} // MIDIUART_rxFifoPeek()

/*
 * Clear the FIFOs and all.
 * This should probably wrap up everything needed to configure the UART for this application.
 */
void MIDIUART_init(void) {
	rxfifoptr.head = 0;
	rxfifoptr.tail = 0;
	rxfifoptr.count = 0;
	txfifoptr.head = 0;
	txfifoptr.tail = 0;
	txfifoptr.count = 0;
	txidle = 1;

} // MIDIUART_init()

/*
 * Write the given message to the UART's transmit FIFO.
 * This will block until the entire message was written to the FIFO.
 */
void MIDIUART_writeMessage(uint8_t *msg, uint8_t msize) {

	while (msize > 0) {
		// block until we have space.
		while (txfifoptr.count >= MIDI_UART_FIFO_SIZE);

		// push the byte.
		txfifobuf[txfifoptr.head] = *msg++;
		txfifoptr.head++;
		if (txfifoptr.head >= MIDI_UART_FIFO_SIZE) {
			txfifoptr.head = 0;
		}
		txfifoptr.count++;
		// If not already busy transmitting, prime the pump.
		if (txidle) {
			EIE2 &= ~EIE2_ES1__ENABLED;
			SCON1 |= SCON1_TI__SET;			// force the interrupt to start sending
			EIE2 |= EIE2_ES1__ENABLED;
		}
		--msize;
	}
}	// MIDIUART_writeMessage

/*
 * Check to see if there is a new packet in the serial receive FIFO.
 * This is implemented as a state machine.
 *
 * The idea is to read the message and parse it, and stuff the results into a four-byte
 * MIDI USB Message Packet. Since there is only one originating port, the cable
 * number is the constant UART_CN (in bsp_config.h).
 *
 * In all cases, when we first get here, if the receive FIFO count is zero, return
 * 0 immediately, indicating nothing to read.
 *
 * We start in the idle state, looking for a status byte.
 * If the count is non-zero, pop the FIFO, and inspect it: is it a status or
 * data byte? If status, determine how many data bytes are associated with the
 * message. This is mostly straightforward, as there are only eight message types.
 *
 * The exception is with SysEx, where any number of bytes may follow the 0xF0 status marker.
 * In this case, read up to four bytes from the FIFO, looking to see if they are the
 * 0xF7 EOX marker. If not, they go into one of the bytes of the MEP.
 *
 * Byte 1 (after the SOX) cannot be 0xF7 as all SysEx messages must have at least
 * one data byte.
 *
 * If byte 2 is EOX, then the CIN code is set to 0x5, mep.byte1 was the 1st data byte read,
 * and we pad byte2 and byte3 with 0x00.
 *
 * If byte 3 is EOX, then the CIN code is set to 0x06, mep.byte1 was the first data byte read,
 * byte2 is the second, and we pad byte3 with 0x00.
 *
 * If byte4 is EOX, then the CIN code is set to 0x07, the mep.byte1, 2, 3 are what was read,
 * and that's the end of our message.
 *
 * If byte4 is not EOX (it's the next data byte), save it for the next time this function is
 * called, and set the CIN code to 0x04.
 *
 * After all of that, set the return value to something non-zero and return. The caller will
 * likely just write the new packet to the USB port.
 *
 * The CIN code is a static variable, so the next time readMessage is called, if it is
 * 0x04 (SysEx starts or continues), we know that we are continuing the handling of a SysEx
 * message.
 *
 *******************************************************************************
 * STATE TABLE.
 *
 * Call the function with a pointer to the USB MIDI message packet buffer, which
 * is four bytes.
 *
 * Start in idle, check count, if zero, return, else pop FIFO. This byte should
 * be STATUS. Parse the status byte and determine how many data bytes are to follow,
 * and what the actual event (CIN and cable number) part of the packet is.
 * Set byte 1 of the packet to this status value.
 * Clear bytes 2 and 3 of the packet, as we may or may not get data for them.
 * Set the byte count and set the state to waiting for byte2.
 *
 * In waiting for data, check rx fifo byte count. If it is zero, exit. The next
 * time this is called it'll jump to this state.
 *
 * If bytes are waiting, read the next byte. Save it in byte2. If this is the
 * last byte of the packet, return true so the caller knows it has a packet and
 * set the state to idle. If not, set the set to waiting for byte3. Check the
 * FIFO count again, if zero, exit, and the next time this is called we jump to
 * the waiting for byte3 state. If there is a byte, read it and save it in byte3.
 * Return true so caller can handle the whole packet. Otherwise return false and
 * deal the next time.
 *
 * If the STATUS byte is SOX, we have to parse differently. That's because the
 * amount of data coming from the sender can be anything, but we have to set the
 * proper code index number for each MIDI USB packet. We need to read at least
 * four bytes from the FIFO to know which CIN to use.
 *
 * So when we see SOX, set the state to SOX1. Check to see if more bytes are available.
 * If not, exit in that state. If so, set the state to SOX1 and read it and save
 * it as byte1. Check count,
 *
 *******************************************************************************
 */
typedef enum {
	MU_IDLE,		// waiting to start a new packet
	MU_DATABYTE2,	// next byte in will be for mep->byte2
	MU_DATABYTE3,	// next byte in will be for mep->byte3
	MU_SYSEX1,		// next byte in is 1st sysex byte, put in mep->byte1
	MU_SYSEX2,		// next byte in is 2nd sysex byte or EOX, put in mep->byte2
	MU_SYSEX3,		// next byte is in 3rd sysex byte or EOX, put in mep-byte3
	MU_SYSEX4		// peek at next byte (don't pop) to see if it's EOX
} MIDIUART_state_t;

// our state register, even though strictly speaking this isn't a state machine.
static MIDIUART_state_t state = MU_IDLE;

bool MIDIUART_readMessage(MIDI_Event_Packet_t *mep) {
	uint8_t newbyte;

	// do nothing if there is nothing to read.
	if (0 == rxfifoptr.count)
		return false;

	// The "State" as such defines our entry point here.
	switch (state) {
	case MU_IDLE :
		newbyte = MIDIUART_rxFifoPop();
		// this has to be a status byte. If it is not, bump out and eventually
		// we'll flush enough and find one.
		if (newbyte < 0x80)
			return false;

		// If it's a SOX byte

		break;
	}
}




uint8_t MIDIUART_readMessage(MIDI_Event_Packet_t *mep) {
	static uint8_t cin = USB_MIDI_CIN_MISC;		// previous Code Index Number
	static uint8_t prev;						// possible 4th SysEx data byte read in previous call
	uint8_t bytecnt;								// count bytes in the packet.
	uint8_t newbyte;								// we just read this from the FIFO.

	if (rxfifoptr.count == 0) {
		// Nothing in the FIFO, so get out.
		return 0;
	}

	// These may not get used for this packet, so clear them.
	mep->byte2 = 0x00;
	mep->byte3 = 0x00;

	/*
	 * If the previous command was the SysEx starts or continues, that means we
	 * previously read four data bytes from the FIFO as part of a long SysEx message.
	 * The fourth byte was saved, so we need to make it part of our message, and
	 * we need to finish that SysEx message.
	 */
	if (cin == USB_MIDI_CIN_SYSEXSTART) {
		mep->byte1 = prev;
		bytecnt = 1;

		while ( ((newbyte = MIDIUART_rxFifoPopBlock()) != MIDI_MSG_EOX) && (bytecnt < 3)) {
			if (bytecnt == 1) {
				mep->byte2 = newbyte;
				bytecnt++;
			} else if (bytecnt == 2) {
				mep->byte3 = newbyte;
				bytecnt++;
			} else if (bytecnt == 3) {
				// if we've read three more data bytes and still haven't reached
				// the end of the packet, we're going to stop here now, and we
				// need to save this byte for next time.
				prev = newbyte;
				// make sure bytecnt reflects how many we actually read.
				bytecnt++;
			} // bytecnt tests
		} // while ...

		// we've read enough. The CIN we send depends on how many bytes we just
		// read.
		if (bytecnt == 1) {
			cin = USB_MIDI_CIN_SYSEND1;
		} else if (bytecnt == 2) {
			cin = USB_MIDI_CIN_SYSEND2;
		} else if (bytecnt == 3) {
			cin = USB_MIDI_CIN_SYSEND3;
		} else if (bytecnt == 4) {
			cin = USB_MIDI_CIN_SYSEXSTART;
		} // bytecnt tree

	} else {
		// Not working on an in-process SysEx message, so pop a new Status byte.
		// If this is NOT a status byte, abort, because we do not expect a
		// data byte here. (If we do abort, eventually other calls to this function
		// will clear out cruft until a new Status byte is seen.)
		newbyte = MIDIUART_rxFifoPop();
		if (newbyte < 0x80)
			return 0;

		// This seems redundant of the above, except where we put the bytes in
		// the message.
		if (newbyte == MIDI_MSG_SOX) {
			// Start of SysEx block. Read up to four more bytes, looking for EOX.
			bytecnt = 0;
			while ( ( (newbyte = MIDIUART_rxFifoPopBlock()) != MIDI_MSG_EOX) && (bytecnt < 3)) {
				if (bytecnt == 0) {
					mep->byte1 = newbyte;
					bytecnt++;
				} else if (bytecnt == 1) {
					mep->byte2 = newbyte;
					bytecnt++;
				} else if (bytecnt == 2) {
					mep->byte3 = newbyte;
					bytecnt++;
				} else if (bytecnt == 3) {
					// we've read enough data bytes to fill the full packet and
					// we also read the next byte, and none are EOX, so stop here,
					// and we need to save this byte for next time.
					prev = newbyte;
					// don't forget this, as we need the correct number of bytes
					// read from the FIFO to determine the Code Index Number.
					bytecnt++;
				} // bytecnt tests
			} // while

			// we've read enough. The CIN we send depends on how many bytes we just
			// read.
			if (bytecnt == 1) {
				cin = USB_MIDI_CIN_SYSEND1;
			} else if (bytecnt == 2) {
				cin = USB_MIDI_CIN_SYSEND2;
			} else if (bytecnt == 3) {
				cin = USB_MIDI_CIN_SYSEND3;
			} else if (bytecnt == 4) {
				cin = USB_MIDI_CIN_SYSEXSTART;
			} // bytecnt tree

		} else {

			// Newbyte _must_ be a status byte. What is it? This will let us
			// fill in the Code Index Number as well as determining how many
			// data bytes will follow.
			// Make sure to mask off the channel number.
			// The "single byte" message cannot originate from the UART, as far
			// as I can tell.
			switch (newbyte & 0xF0) {
			case MIDI_MSG_NOTEOFF :
				cin = USB_MIDI_CIN_NOTEOFF;
				bytecnt = 2;
				break;
			case MIDI_MSG_NOTEON :
				cin = USB_MIDI_CIN_NOTEON;
				bytecnt = 2;
				break;
			case MIDI_MSG_POLYPRESSURE :
				cin = USB_MIDI_CIN_POLYKEYPRESS;
				bytecnt = 2;
				break;
			case MIDI_MSG_CTRLCHANGE :
				cin = USB_MIDI_CIN_CTRLCHANGE;
				bytecnt = 2;
				break;
			case MIDI_MSG_PROGCHANGE :
				cin = USB_MIDI_CIN_PROGCHANGE;
				bytecnt = 1;
				break;
			case MIDI_MSG_CHANNELPRESSURE :
				cin = USB_MIDI_CIN_CHANPRESSURE;
				bytecnt = 1;
				break;
			case MIDI_MSG_PITCHBEND :
				cin = USB_MIDI_CIN_PITCHBEND;
				bytecnt = 2;
				break;
			case MIDI_MSG_SOX :
				// this is cheating, because I don't handle SOX here, but I need
				// to handle the other System Common messages.
				switch (newbyte) {
				case  MIDI_MSG_MTCQF :
				case  MIDI_MSG_SS :
					// two-byte System Common (one data byte)
					cin = USB_MIDI_CIN_SYSCOM2;
					bytecnt = 1;
					break;
				case MIDI_MSG_SPP :
					// three byte System Common (two data bytes)
					cin = USB_MIDI_CIN_SYSCOM3;
					bytecnt = 2;
					break;
				case MIDI_MSG_F4 :
				case MIDI_MSG_F5 :
				case MIDI_MSG_TUNEREQ :
					// one byte System Common (no data byte)
					cin = USB_MIDI_CIN_SYSEND1;
					bytecnt = 0;
					break;
				default :
					// the reset are Real Time messages with no data.
					cin = USB_MIDI_CIN_SINGLEBYTE;
					bytecnt = 0;
					break;
				} // inner switch
				break;
			default:
				// not possible.
				break;
			} // switch

			// The status byte is byte 1 of our packet.
			mep->byte1 = newbyte;
			// Now read this packet's data bytes from the FIFO.
			// we can destroy prev as it is not used for non-SysEx packets.
			for (prev = 0; prev < bytecnt; prev++) {
				newbyte = MIDIUART_rxFifoPopBlock();
				if (bytecnt == 0) {
					mep->byte2 = newbyte;
				} else if (bytecnt == 1) {
					mep->byte3 = newbyte;
				}
			}
		} // if newbyte == SOX
	} // if cin == USB_MIDI_CIN_SYSEXSTART

	// Success!
	// finish the packet.
	mep->event = USB_MIDI_EVENT(UART_CN, cin);

	return 4;
} //MIDIUART_readMessage
