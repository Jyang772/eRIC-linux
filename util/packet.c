#include "packet.h"

unsigned int CRC_calculate(Packet* data) {
	return crc32a(data->payload);
}

int CRC_verify(Packet data) {
	
	if(data.CRC != crc32a(data.payload))
		return -1;
	else
		return 1;
}

Packet* new_packet(char* type, char* srcAddr, char* destAddr, int seqNum, char* payload, char* CRC) {

}

void free_packet(Packet* data) {

	free(data->srcAddr);
	free(data->destAddr);
}
