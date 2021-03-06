/*
Copyright (c) 2017, Justin S Yang

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted, provided
that the above copyright notice and this permission notice appear
in all copies.
THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

*/

/**
 * @file packet.h
 *
 * @brief Description of Packet structure
 *
 */

#ifndef PACKET_H
#define PACKET_H

#include "crc.h"
#include <stdio.h>
#include <stdlib.h>

#define INVITE "0000"
#define TEMP "0111"

/**
 * A Packet structure. New Packets can be created using the new_packet function.
 *
 * @see packet_new
 */

typedef struct Packet{

	/**  Type of transmission */
	char type[5];
	/** Source address */
	char srcAddr[6];
	//char* srcAddr;
	/** Destination address */
	char destAddr[6];
	//char* destAddr;
	/** Sequence number used for determining flow of transmission */
	int seqNum;
	/** Payload */
	char payload[160];
	/** CRC */
	unsigned int CRC;
} Packet;

/**
 * Calculate CRC and attach to end of Packet structure.
 *
 * @return 8 byte CRC value.
 */

unsigned int CRC_calculate(Packet* data);

/**
 * Verify CRC
 *
 * @return -1 if CRC verification fails.
 */

int CRC_verify(Packet data);

/**
 * Serializes a Packet for sending/receiving.
 */

void serialize_Packet(Packet* data);

/**
 * Cleans and destroys packet. Call when a packet has been sent or received.
 *
 */

Packet* new_packet(char* type, char* srcAddr, char* destAddr, int seqNum, char* payload, char* CRC);

void free_packet(Packet* data);

#endif
