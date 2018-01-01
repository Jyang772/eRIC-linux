//#include "readLine.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


//Radio Struct
typedef struct Radio{

	char* ID;
	char* destAddr;
	//String operations
	//void sendMsg(char**);
	//Operations
	void (*setDestination)(struct Radio*, char*);
	void (*getTemp)(struct Radio*, char*);
	void (*listen)(struct Radio*, char*);
} Radio;


void setDestination(Radio*, char*);
void listen(Radio*, char*);
Radio* init_Radio(char* name);
int setup_interface(int* fd,char* portname, int BAUD_RATE);
int getTemp(Radio*, char*);


