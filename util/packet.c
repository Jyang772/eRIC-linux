#include "packet.h"

unsigned int CRC_calculate(Packet* data) {
	return crc32a(data->payload);
}

int CRC_verify(Packet data) {
	
	if(crc32a(data.CRC) != crc32a(data.payload))
		return -1;
	else
		return 1;
}


void free_packet(Packet* data) {

	free(data->srcAddr);
	free(data->destAddr);
}
