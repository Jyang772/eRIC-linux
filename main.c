#include "util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <poll.h>

struct pollfd fds[1];
int timeout;

void write_data(Packet* data )
{
   int fd = 0;
   /* open the file in append mode */
   fd = open( "data.dat", O_RDWR|O_CREAT|O_APPEND,S_IWUSR |S_IRUSR);
   
   /* write the binary structure right to the file */
   write(fd,data,sizeof(Packet));
   close(fd);
}


void read_data()
{
   int fd = 0;
   Packet data;

   /* open the file */
   fd = open( "data.dat", O_RDONLY );
   while(read(fd, &data, sizeof(Packet))){}

   printf("type: %s\n",data.type);
   printf("src: %s\n",data.srcAddr);
   printf("dest: %s\n",data.destAddr);
   printf("payload: %s\n",data.payload);

   /* close file */
   close(fd);
}

int main() {


	//Determine which /dev/ file is the device on
	char* name = "A";
	char* portname = "/dev/ttyUSB1";
	int fd = 0;
	int wlen = 0;
	int BAUD_RATE = B19200;

	//Define and Initiate Radio Structs
	/*
	Radio radA = {
		.ID = "A",
		.setDestination = setDestination
	};
	*/

	Radio* radA = init_Radio(name);
	setup_interface(radA, &fd, portname, BAUD_RATE);

	printf("Name: %s\n",radA->ID);
	radA->setDestination(radA,"B");
	printf("Destination: %s\n",radA->destAddr);
	
	//radA->init_connection(radA);
	tcflush(fd, TCIOFLUSH);

	fds[0].fd = fd;
	fds[0].events = 0;
	fds[0].events |= POLLIN;
	timeout = 1000;
	int pret;
	int bytes;

	while(1) {
		radA->init_connection(radA);
		pret = poll(fds, 1, timeout);
		if(pret == 0) {
			printf("ret %d\n",pret);
			printf("\ttimeout\n");
		}
		else {
		//int bytes;
		//ioctl(fd, FIONREAD, &bytes);
		
		Packet data;
		int rd = safe_read(fd, &data, sizeof(Packet)); /* Check for errors */
		
		if(rd > 0)
			printf("d: %s\n",data.type);
		}	
		sleep(1);
	}

	//radA->sendCmd("CMD");
	//radA->getTemp();
	//radA->close_connection();
	//
	//
	
	/*
	if(strcmp(data.type,"0000") == 0)
		printf("Type 1\n");

	printf("Size of packet: %d\n",sizeof(data));

	printf("%s\n",data.srcAddr);
	free_packet(&data);
	printf("%s\n",data.srcAddr);
	*/


	/*
	Packet data;
	strcpy(data.type,"0000");
	strcpy(data.srcAddr,"A");
	strcpy(data.destAddr,"B");
	strcpy(data.payload,"lol");

	write_data(&data);
	read_data();
	strcpy(data.type,"s");
	write_data(&data);
	read_data();
	strcpy(data.type, "end");
	write_data(&data);
	read_data();
*/	

}
