#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

typedef struct Packet {

	char type[50];
	char srcAddr[50];
	char destAddr[50];
	char payload[50];
} Packet;

void write_data(Packet* data)
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

int safe_read(int fd, const void *p, size_t want){
    int ret;
    int ret_sum = 0;

    errno = 0;
    while (want){
        ret = read(fd, (uint8_t*)p, want);
        if(ret == 0)
            return -1; /* EOF */
        if(ret <= 0){
            if(errno != EINTR && errno != EAGAIN ) {
                return -1;
            }
            errno = 0;
            continue;
        }
        want -= ret;
        p = (uint8_t*) p + ret;
        ret_sum += ret;
    }
    return ret_sum;
}

int safe_write(int fd, const void *p, size_t want){
    int ret;
    int ret_sum = 0;

    errno = 0;
    while(want){
        ret = write(fd, (uint8_t *)p,want);
        if(ret <= 0) {
            if (errno != EINTR && errno != EAGAIN){
                return -1;
            }
            errno = 0;
            continue;
        }
        want -= ret;
        p = (uint8_t*) p + ret;
        ret_sum += ret;
    }
    return ret_sum;
}


int main() {

	struct Packet lol = {"hello","pingu","noots","noot!"};

	//write_data(&lol);

	//read_data();

	int fd = 0;
	fd = open("data.dat", O_RDONLY);

	safe_write(fd,&lol, sizeof(Packet));
	Packet data;
	safe_read(fd,&data, sizeof(Packet));

	printf("payload: %s\n",data.payload);

}
