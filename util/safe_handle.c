#include "safe_handle.h"

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
