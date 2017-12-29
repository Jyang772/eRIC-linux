#include "util.h"

void setDestination(Radio* r, char* s) {

	r->destAddr = strdup(s);
	assert(strcmp(r->destAddr,s) == 0);
	return;
}
