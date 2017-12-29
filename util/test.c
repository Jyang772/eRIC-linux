#include "util.h"
#include <stdlib.h>
#include <stdio.h>


void printOut(Radio);

int main() {

	Radio pingu;
	pingu.setDestination = setDestination;
	pingu.setDestination(&pingu,"A");
	printOut(pingu);




	return 0;
}

void printOut(Radio p) {
	printf("%s\n",p.destAddr);
}

