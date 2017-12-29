//#include "readLine.h"
#include <assert.h>

//Radio Struct
typedef struct {

	char* destAddr;
	//String operations
	//void sendMsg(char**);

	//Operations
	void (*setDestination)(struct Radio*, char*);
} Radio;


void setDestination(Radio*, char*);


