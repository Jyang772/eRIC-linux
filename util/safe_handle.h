#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <errno.h>

int safe_write(int fd, const void *p, size_t want);

int safe_read(int fd, const void *p, size_t want);
