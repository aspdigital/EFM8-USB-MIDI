/*
 * midi_uart.c
 *
 *  Created on: Apr 20, 2019
 *      Author: andy
 *
 *  Mods:
 *  2019-05-21 andy: MIDIUART_writeMessage() returns true if the serial transmit
 *  	FIFO has room for another four messages that is, it is below its almost-
 *  	full threshold. This is used to determine whether the OUT endpoint, which
 *  	is the source of data for the messages, should be armed again with a call
 *  	to USBD_Read().
 *
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

// This is the almost-full threshold. It allows for at least one full endpoint
// packet's worth of messages (four messages, 24 bytes total) plus some
// headroom.
#define MIDI_UART_ALMOST_FULL (MIDI_UART_FIFO_SIZE - 32)

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
		P3_B7= ~P3_B7;
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
 * Clear the FIFOs and all.
 * This should probably wrap up everything needed to configure the UART for this application.
 */
void MIDIUART_init(void) {
#if 1
	// useful for debug!
	for (rxfifoptr.count = 0;rxfifoptr.count < MIDI_UART_FIFO_SIZE; rxfifoptr.count++) {
		rxfifobuf[rxfifoptr.count] = 0;
		txfifobuf[rxfifoptr.count] = 0;
	}
#endif

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
 * We don't have to be concerned that the FIFO will overflow, as we'll hold off
 * USB OUT transactions if there isn't enough space here.
 * We return TRUE if there _is_ space in the FIFO for another USB OUT packet's
 * worth of messages.
 */
bool MIDIUART_writeMessage(uint8_t *msg, uint8_t msize)
{
	while (msize > 0)
	{
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
	return (txfifoptr.count < MIDI_UART_ALMOST_FULL);
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
	MU_SYSEX1,		// next byte in is 1st sysex byte, put in mep->byte2
	MU_SYSEX2		// next byte in is 2nd sysex byte or EOX, put in mep->byte3
} MIDIUART_state_t;


bool MIDIUART_readMessage(MIDI_Event_Packet_t *mep) {
	// these are newly assigned at every call.
	bool done;				// indicates packet finished or not, the return value
	uint8_t newbyte;		// read from FIFO
	// saved each time through.
	static uint8_t cin;			// Code Index Number for this packet
	static uint8_t bytecnt;		// iterator for data bytes in this packet
	static uint8_t bytesinpacket;	// set by status parser for running status.
	static MIDIUART_state_t state = MU_IDLE;

	// start not done, obviously. This will be set as necessary.
	done = false;

	// now stay here until we've read and handled an entire packet, or we've
	// emptied the receive FIFO and we have to wait for more bytes.

	while (!done && (rxfifoptr.count > 0)) {
		switch (state) {
			case MU_IDLE :
				// clear byte2 and byte3 here, on the chance that this newest message
				// will not need them.
				mep->byte2 = 0x00;
				mep->byte3 = 0x00;

				// Get the next byte in the FIFO.
				newbyte = MIDIUART_rxFifoPop();

				// Is it a SOX byte?
				if (newbyte == MIDI_MSG_SOX) {
					// SYSEX messages require at least one data byte before EOX, so
					// we must fetch it. At this point we don't know which CIN to use.
					// But we do know that byte1 is the SOX byte.
					mep->byte1 = MIDI_MSG_SOX;
					state = MU_SYSEX1;

				} else if (newbyte < 0x80) {
					// running status now active. Use the previous CIN/CN and
					// byte1 (the previous status). The byte we just read is
					// byte2 of the packet.
					mep->byte2 = newbyte;

					// See if we need one more byte to complete the packet.
					// If so, wait for it, otherwise this packet is done.
					if (bytesinpacket == 2) {
						// yes, one more data byte to fetch:
						state = MU_DATABYTE3;
					} else {
						// no more for this packet, send it. Note we cleared byte
						// at entry to this state.
						state = MU_IDLE;
						done = true;
					} // bytes in packet

				} else {

					// not SOX, but it is some kind of status.
					// What is it? This will let us fill in the Code Index Number
					// as well as determining how many data bytes will follow.
					// Make sure to mask off the channel number.
					// The "single byte" message cannot originate from the UART, as far
					// as I can tell.

					switch (newbyte & 0xF0) {
					case MIDI_MSG_NOTEOFF :
						cin = USB_MIDI_CIN_NOTEOFF;
						bytesinpacket = 2;
						break;
					case MIDI_MSG_NOTEON :
						cin = USB_MIDI_CIN_NOTEON;
						bytesinpacket = 2;
						break;
					case MIDI_MSG_POLYPRESSURE :
						cin = USB_MIDI_CIN_POLYKEYPRESS;
						bytesinpacket = 2;
						break;
					case MIDI_MSG_CTRLCHANGE :
						cin = USB_MIDI_CIN_CTRLCHANGE;
						bytesinpacket = 2;
						break;
					case MIDI_MSG_PROGCHANGE :
						cin = USB_MIDI_CIN_PROGCHANGE;
						bytesinpacket = 1;
						break;
					case MIDI_MSG_CHANNELPRESSURE :
						cin = USB_MIDI_CIN_CHANPRESSURE;
						bytesinpacket = 1;
						break;
					case MIDI_MSG_PITCHBEND :
						cin = USB_MIDI_CIN_PITCHBEND;
						bytesinpacket = 2;
						break;
					case MIDI_MSG_SOX :
						// this is cheating, because I don't handle SOX here, but I need
						// to handle the other System Common messages.
						switch (newbyte) {
						case  MIDI_MSG_MTCQF :
						case  MIDI_MSG_SS :
							// two-byte System Common (one data byte)
							cin = USB_MIDI_CIN_SYSCOM2;
							bytesinpacket = 1;
							break;
						case MIDI_MSG_SPP :
							// three byte System Common (two data bytes)
							cin = USB_MIDI_CIN_SYSCOM3;
							bytesinpacket = 2;
							break;
						case MIDI_MSG_F4 :
						case MIDI_MSG_F5 :
						case MIDI_MSG_TUNEREQ :
							// one byte System Common (no data byte)
							cin = USB_MIDI_CIN_SYSEND1;
							bytesinpacket = 0;
							break;
						default :
							// the rest are Real Time messages with no data.
							cin = USB_MIDI_CIN_SINGLEBYTE;
							bytesinpacket = 0;
							break;
						} // inner switch (if MIDI_MSG_SOX)
						break;
					default:
						// not possible.
						break;
					} // switch (newbyte & 0xF0)

					// now we know how many bytes we need to fetch from the FIFO
					// to finish up this packet, so set the next state properly.
					if (0 == bytesinpacket) {
						// we do not need to fetch any more bytes for this packet.
						done = true;
						state = MU_IDLE;
					} else {
						// we need to fill at least mep->byte2 and possibly byte3
						bytecnt = bytesinpacket;
						state = MU_DATABYTE2;
					}

					// The status byte is byte 1 of our packet.
					mep->byte1 = newbyte;

					// and we know the event header byte from the Code Index Number
					// we set above.
					mep->event = USB_MIDI_EVENT(UART_CN, cin);

				} // if newbyte
				break; // out of idle.

			case MU_DATABYTE2 :
				// the next thing in the FIFO is byte2 of the midi event packet.
				mep->byte2 = MIDIUART_rxFifoPop();
				--bytecnt;

				// if there is one more byte in this packet, we have to read it,
				// otherwise we are done.
				if (bytecnt) {
					state = MU_DATABYTE3;
				} else {
					state = MU_IDLE;
					done = true;
				}
				break;

			case MU_DATABYTE3 :
				// get the last byte of the packet from the serial receive FIFO,
				// and we are done. we no longer care about bytecnt.
				mep->byte3 = MIDIUART_rxFifoPop();
				done = true;
				state = MU_IDLE;
				break;

			case MU_SYSEX1 :
				// we are here because we got a SOX byte. There must be at least
				// one data byte in a SYSEX packet, so read it from the FIFO.
				mep->byte2 = MIDIUART_rxFifoPop();

				// if this byte is EOX, then this is that special two-byte SysEx
				// packet, which means we are done. it also means we know which
				// CIN to assign.
				if (mep->byte2 == MIDI_MSG_EOX) {
					mep->event = USB_MIDI_EVENT(UART_CN, USB_MIDI_CIN_SYSEND2);
					done = true;
					state = MU_IDLE;
				} else {
					// there is at least one more data byte, so go fetch it.
					state = MU_SYSEX2;
				}
				break;

			case MU_SYSEX2 :
				// we are here because we are in a SysEx packet and there is another
				// byte for it. This will fill the MIDI packet byte 3.
				mep->byte3 = MIDIUART_rxFifoPop();

				// if this byte is EOX, then we have the special three-byte SysEx
				// packet, which means we are done. It also means we know which CIN
				// to assign.
				if (mep->byte3 == MIDI_MSG_EOX) {
					mep->event = USB_MIDI_EVENT(UART_CN, USB_MIDI_CIN_SYSEND3);
					state = MU_IDLE;
				} else {
					// it's not the end of the packet. There is more. But we have
					// completely filled our MIDI packet, so send it off.
					mep->event = USB_MIDI_EVENT(UART_CN, USB_MIDI_CIN_SYSEXSTART);
					// but we know that the next byte in the serial receive FIFO is
					// part of the SysEx message, so go get it.
					state = MU_SYSEX1;
				}

				// in any case if we are in this state we've filled an entire packet
				// so send it.
				done = true;

				break;

			default :
				// never get here.
				break;
		} // end of state register switch
	} // end of while (we've got something to read and process

	// tell caller if we have a complete packet or not.
	return done;
} // bool readMessage()
