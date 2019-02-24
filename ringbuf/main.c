#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "ringbuf.h"

void thread_snd(void *);
void thread_rcv(void *);
void err_sys(char *s);

int main(void)
{
	int ret;
	pthread_t tid1, tid2;

	ret = ringbuf_create(10, 4);
	if (ret != 0)
		err_sys("ringbuf_create() error");

	ret = pthread_create(&tid1, NULL, (void *)(*thread_snd), NULL);
	if (ret != 0)
		err_sys("pthread_create() error");

	ret = pthread_create(&tid2, NULL, (void *)(*thread_rcv), NULL);
	if (ret != 0)
		err_sys("pthread_create() error");

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}

void thread_snd(void *args)
{
	int ret;
	int a[1000];

	for (int i = 0; i < 1000; i++)
	{
		a[i] = i;
again:
		ret = ringbuf_snd(a[i]);
		if (ret != 0)
		{
			if (ret == 1)
				goto again;
			err_sys("ringbuf_snd() error");
		}
	}

	pthread_exit(NULL);
}

void thread_rcv(void *args)
{
	int ret, val;

	for (int i = 0; i < 1000; i++)
	{
again:
		ret = ringbuf_rcv(&val);
		if (ret != 0)
		{
			if (ret == 1)
				goto again;
			err_sys("ringbuf_rcv() error");
		}
		printf("%d\n", val);
	}

	pthread_exit(NULL);
}

void err_sys(char *s)
{
	fprintf(stderr, "%s:%d  %s\n", __FILE__, __LINE__, s);
	exit(1);
}
