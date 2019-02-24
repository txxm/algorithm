#include <stdio.h>

#ifndef	__RINGBUF__
#define __RINGBUF__

int32_t *pBuf;
size_t n_count;
size_t i_snd;
size_t i_rcv;

int32_t ringbuf_create(size_t count, size_t nbyte);
int32_t ringbuf_snd(int32_t data);
int32_t ringbuf_rcv(int32_t *pval);

#endif
