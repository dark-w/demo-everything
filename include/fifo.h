#ifndef FIFO_H
#define FIFO_H

#include <string.h>

//#define FIFO_SAFE_CHECK

#define bzero(ptr, size) mem_set(ptr, 0, size)

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

#define FIFO_BUFFER_SIZE 512

struct fifo {
    uint8_t buffer[FIFO_BUFFER_SIZE];
    uint8_t *pread;
    uint8_t *pwrite;
    uint32_t count;
};

static inline void fifo_init(struct fifo *pfifo)
{
    bzero(pfifo->buffer, FIFO_BUFFER_SIZE);
    pfifo->pread = pfifo->pwrite = pfifo->buffer;
    pfifo->count = 0;
}

void fifo_read(struct fifo *pfifo, uint8_t *buffer, uint32_t len);
void fifo_write(struct fifo *pfifo, const uint8_t *buffer, uint32_t len);

#endif // FIFO_H
