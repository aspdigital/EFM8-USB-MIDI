/*
 * midi.h
 *
 *  Created on: Apr 20, 2019
 *      Author: andy
 *
 * MIDI functions and definitions.
 *
 * This module abstracts access to MIDI events, meaning it doesn't assume that the transport
 * is UART or USB.
 */

#ifndef MIDI_H_
#define MIDI_H_

#include "si_toolchain.h"

/*
 * MIDI Message Packets.
 */
typedef struct
{
	uint8_t byte1;		// MIDI_0
	uint8_t byte2;		// MIDI_1
	uint8_t byte3;		// MIDI_2
} MIDI_Message_t;


/*
 * Define the various MIDI message types.
 */
#define MIDI_MSG_NOTEOFF         0x80
#define MIDI_MSG_NOTEON          0x90
#define MIDI_MSG_POLYPRESSURE    0xA0
#define MIDI_MSG_CTRLCHANGE      0xB0
#define MIDI_MSG_PROGCHANGE      0xC0
#define MIDI_MSG_CHANNELPRESSURE 0xD0
#define MIDI_MSG_PITCHBEND       0xE0
#define MIDI_MSG_SOX             0xF0
#define MIDI_MSG_MTCQF 			 0xF1
#define MIDI_MSG_SPP             0xF2
#define MIDI_MSG_SS              0xF3
#define MIDI_MSG_F4              0xF4
#define MIDI_MSG_F5              0xF5
#define MIDI_MSG_TUNEREQ         0xF6
#define MIDI_MSG_EOX             0xF7
#define MIDI_MSG_TIMINGCLOCK     0xF8
#define MIDI_MSG_F9              0xF9
#define MIDI_MSG_START           0xFA
#define MIDI_MSG_CONTINUE        0xFB
#define MIDI_MSG_STOP            0xFC
#define MIDI_MSG_FD              0xFD
#define MIDI_MSG_ACTIVESENSING   0xFE
#define MIDI_MSG_SYSRST          0xFF

/*
 * Construct a MIDI STATUS byte from a given MIDI message and channel.
 */
#define MIDI_STATUS_BYTE(message, channel)  (message | channel)

#endif /* MIDI_H_ */
