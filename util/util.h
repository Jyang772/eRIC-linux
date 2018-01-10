#ifndef UTIL_H
#define UTIL_H

#include "readLine.h"
#include "packet.h"
#include "safe_handle.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <poll.h>

/**
 * Radio struct
 */

typedef struct Radio{

	int fd;
	char* ID;
	char* destAddr;
	//String operations
	//void sendMsg(char**);
	//Operations
	void (*setDestination)(struct Radio*, char*);
	int (*getTemp)(struct Radio*);
	void (*listen)(struct Radio*);
	int (*init_connection)();

	//Send/Receive
	int (*send)();
	int (*receive)();
	
	struct pollfd fds[1];
} Radio;


void setDestination(Radio*, char*);

/**
 * Initiates connection between two Radio nodes.
 *
 * @return Positive value if connection is established. Negative value if connection fails.
 */

int init_connection(Radio*);

/**
 * Sends a Packet to the Radio destination.
 *
 * @return Positive value if Packet sent successfully.
 */
int send(Radio*, Packet);
void listen(Radio*);
Radio* init_Radio(char* name);
int setup_interface(Radio* r, int* fd,char* portname, int BAUD_RATE);
int getTemp(Radio*);
int _getTemp(Radio*); //internal

int read_reply(Radio*);


#endif
