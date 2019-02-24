#include <stdio.h>
#include <stdlib.h>

#include "ringbuf.h"


/*创建环形队列*/
int32_t ringbuf_create(size_t count, size_t nbyte)
{
	n_count = count;

	pBuf = (int32_t *)malloc(sizeof(int32_t) * count);
	if (!pBuf)
		return 1;

	return 0;
}

/*向环形队列发送数据*/
int32_t ringbuf_snd(int32_t data)
{
	if ((i_snd + 1) % n_count == i_rcv)
		return 1;
	else
	{
		pBuf[i_snd] = data;
		i_snd++;
		i_snd %= n_count;
	}

	return 0;
}

/*从环形队列读取数据*/
int32_t ringbuf_rcv(int32_t *pval)
{
	if (i_rcv == i_snd)
		return 1;
	else
	{
		*pval = pBuf[i_rcv];
		i_rcv++;
		i_rcv %= n_count;
	}

	return 0;
}
