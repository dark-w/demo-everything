#include "fifo.h"

#include <stdio.h>

#define FIFO_OVERFLOW 0

void fifo_read(struct fifo *pfifo, uint8_t *buffer, uint32_t len)
{
#ifdef FIFO_SAFE_CHECK
    if (!pfifo || !buffer) {
        return;
    }
#endif

    uint8_t *pr = pfifo->pread;

    uint8_t *const pfifo_buffer_end = pfifo->buffer + FIFO_BUFFER_SIZE;
    uint8_t *const pfifo_buffer_begin = pfifo->buffer;

    uint32_t l = len > pfifo->count ? pfifo->count : len;

    if (FIFO_OVERFLOW == pr) {
        pr = pfifo->pwrite;
    }

    // update the fifo
    pfifo->count -= l;
    pfifo->pread = pr + l > pfifo_buffer_end ?
                       pfifo_buffer_begin + (l - (pfifo_buffer_end - pr)) :
                       pr + l;

BEGIN_READ:

    while (pr < pfifo_buffer_end && l != 0) {
        *buffer++ = *pr++;
        l--;
    }

    if (l != 0) {
        pr = pfifo_buffer_begin;
        goto BEGIN_READ;
    }
}

void fifo_write(struct fifo *pfifo, const uint8_t *buffer, uint32_t len)
{
#ifdef FIFO_SAFE_CHECK
    if (!pfifo || !buffer) {
        return;
    }
#endif
    uint8_t *pw = pfifo->pwrite;

    uint8_t *const pfifo_buffer_begin = pfifo->buffer;
    uint8_t *const pfifo_buffer_end = pfifo->buffer + FIFO_BUFFER_SIZE;

    uint8_t l = len;

    for (uint8_t i = 0; i < l; i++) {
        *pw++ = *buffer++;

        if (pw == pfifo_buffer_end) {
            pw = pfifo_buffer_begin;
        }
    }

    uint32_t count = pfifo->count + l;

    if (count > FIFO_BUFFER_SIZE) {
        count = FIFO_BUFFER_SIZE;
    }

    pfifo->pwrite = pw;
    pfifo->count = count;
}
