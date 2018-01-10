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

/*
	struct pollfd fds[1];
	int timeout = 2000;	
        fds[0].fd = r->fd;
        fds[0].events = 0;
        fds[0].events |= POLLIN;
*/

	Packet data;
	strncpy(data.type,"0000",5); //include null term
	strncpy(data.srcAddr,r->ID, 6);
	strncpy(data.destAddr,r->destAddr,6);

	if(send(r, data) > 0) {
		int rd = 0;
		read_reply(r);

                rd = safe_read(r->fd, &data, sizeof(Packet));
                if(rd > 0) {
                        /* get Packet type */
			if(strcmp(data.type,"0010") == 0) {
				printf("ACK received\n");
				return 1;
			}
                }	


	}
}

int send(Radio* r, Packet data) {
	printf("Send\n");

	int wlen;
	int fd;
	fd = r->fd;

	wlen = safe_write(fd, &data, sizeof(Packet));
	if(wlen != sizeof(Packet)) {
		printf("Error from write: %d, %d\n", wlen, errno);
	}
}

void listen(Radio* r) {

	while(1) {
		int rdlen;
		int bytes;

		Packet data;
		ioctl(r->fd, FIONREAD, &bytes);
		if(bytes != sizeof(Packet)) {
			continue;
		}
			
		printf("listen_bytes: %d\n",bytes);
		
		rdlen = safe_read(r->fd, &data, sizeof(Packet));
			
		if(rdlen > 0) {
			printf("rdlen: %d\n",rdlen);
			printf("%s\n",data.type);
			if(strcmp(data.type,INVITE) == 0) {
				printf("INVITE!\n");
				Packet reply;
				strcpy(reply.type,"0010");
				send(r,reply);
				//write(r->fd, &reply, sizeof(Packet));
			}

			if(strcmp(data.type,TEMP) == 0) {
				tcflush(r->fd, TCIOFLUSH);
				printf("TEMP REQUESTED\n");
				_getTemp(r);
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
	new_Radio->getTemp = getTemp;


	return new_Radio;
}

int getTemp(Radio* r) {

	Packet data;
	strncpy(data.type,"0111",5);
	strncpy(data.srcAddr,r->ID,6);
	strncpy(data.destAddr,r->destAddr,6);

	if(send(r,data) > 0) {
		int rd = 0;
		read_reply(r);

		rd = safe_read(r->fd, &data, sizeof(Packet));
		printf("%d\n",rd);
		if(rd > 0) {
			/* get Packet payload and verify CRC */
			if(CRC_verify(data) > 0) {
				printf("Temp: %s\n",data.payload);
				return 1;
			}
			else {
				printf("Packet corrupt\n");
				tcflush(r->fd, TCIOFLUSH);
				return -1;
			}
		} else {
			return -1;
		}
	} else {
		return -1;
	}
}

int _getTemp(Radio* r) {

	unsigned char buf[80];
	int wlen = 0;
	wlen = write(r->fd, "ER_CMD#T7", 9);

	tcdrain(r->fd);
	usleep(800000);
	tcflush(r->fd, TCIOFLUSH);
	wlen = write(r->fd, "ACK", 3);
	usleep(50000);
	readLine(r->fd, buf, 80);
	buf[strlen(buf)] = '\n';
	buf[strlen(buf)+1] = 0;
	
	printf("Temp: %s\n",buf);

	
	Packet temp;
	strncpy(temp.type,"0111",5);
	strncpy(temp.srcAddr,r->ID,6);
	strncpy(temp.destAddr,r->destAddr,6);
	temp.seqNum = 1;
	strncpy(temp.payload,buf,strlen(buf)+1);
	temp.CRC = CRC_calculate(&temp);
	send(r,temp);

}

int read_reply(Radio* r) {

	struct pollfd fds[1];
	int timeout = 2000;

	fds[0].fd = r->fd;
	fds[0].events = 0;
	fds[0].events |= POLLIN;

	int rd = 0;
	int bytes, pret;

	while(1) {
			pret = poll(fds, 1, timeout);
			if(pret == 0) {
				tcflush(r->fd, TCIOFLUSH);
				printf("timeout\n");
				sleep(1);
				return -1;
			}
			else {
				ioctl(r->fd, FIONREAD, &bytes);
				if(bytes < sizeof(Packet)) {
					continue;
				}
				else
					break;
			}
		}
}


