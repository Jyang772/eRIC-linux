//#include "readLine.h"
#include "packet.h"
#include "safe_handle.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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
	void (*getTemp)(struct Radio*, char*);
	void (*listen)(struct Radio*);
	int (*init_connection)();

	//Send/Receive
	int (*send)();
	int (*receive)();
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
int getTemp(Radio*, char*);



