#include "util.h"
#include "interface.h"

void setDestination(Radio* r, char* s) {

	printf("setDestination\n");

	r->destAddr = strdup(s);
	assert(strcmp(r->destAddr,s) == 0);
	return;
}

int init_connection(Radio* r) {
	//Send connection request
	//Construct Connection request packet

	printf("init_connection\n");	
	
	Packet data;
	strncpy(data.type,"0000",5); //include null term
	strncpy(data.srcAddr,r->ID, 6);
	strncpy(data.destAddr,r->destAddr,6);

	/*
	Packet data = { 
		.type = strdup("0000"),
		.srcAddr = strdup(r->ID),
		.destAddr = strdup(r->destAddr),
	};
	*/
	
	if(send(r, data) > 0)
		return 1;
	else
		return -1;
}

int send(Radio* r, Packet data) {
	printf("Send\n");

	int wlen;
	int fd;
	fd = r->fd;

	wlen = write(fd, &data, sizeof(Packet));
	if(wlen != sizeof(Packet)) {
		printf("Error from write: %d, %d\n", wlen, errno);
	}
}

void listen(Radio* r) {

	while(1) {
		int rdlen;
		Packet data;
		rdlen = read(r->fd, &data, sizeof(Packet));
		tcdrain(r->fd);
		
		if(rdlen > 0) {
			if(strcmp(data.type,INVITE) == 0) {
				printf("INVITE!\n");
				Packet reply;
				strcpy(reply.type,"0010");
				write(r->fd, &reply, sizeof(Packet));
			}	
		}

	}
	

}

int setup_interface(Radio* r, int* fd, char* portname, int BAUD_RATE) {

	*fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if(*fd < 0) {
		printf("Error opening %s: %s\n", portname, strerror(errno));
		return -1;
	}

	set_interface_attribs(*fd, BAUD_RATE);
	r->fd = *fd;

	return 1;
}

Radio* init_Radio(char* name) {

	Radio* new_Radio = (Radio*)malloc(sizeof(Radio));

	new_Radio->ID = strdup(name);
	new_Radio->setDestination = setDestination;
	new_Radio->init_connection = init_connection;
	new_Radio->listen = listen;


	return new_Radio;
}

int getTemp(Radio* r, char* s) {

}

