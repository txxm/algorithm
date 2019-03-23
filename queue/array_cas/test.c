#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "casarray.h"

cas_node_t *cas_queue;

void *thread_read(void *args)
{
	int ret;
	char buf[1024];

	pthread_detach(pthread_self());
	while(1)
	{
		//sleep(1);
		memset(buf, 0, 1024);
		ret = cas_read(buf);
		if (ret != CAS_OK) {
			//printf("%s", cas_strerror(ret));
			continue;
		}
		printf("%s", buf);
	}
	pthread_exit(NULL);
}

void *thread_write(void *args)
{
	int ret;
	char buf[1024];
	time_t timer;
	struct tm *tblock;

	pthread_detach(pthread_self());
	while(1)
	{
		//sleep(1);
		timer = time(NULL);
		tblock = localtime(&timer);
		memset(buf, 0, 1024);
		sprintf(buf, "%s", asctime(tblock));
		ret = cas_write(buf);
		if (ret != CAS_OK) {
			//printf("%s\n", cas_strerror(ret));
			continue;
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int i;
	pthread_t tid[5];
	pthread_t tid2[5];

	cas_queue = cas_init(12800);
	if (cas_queue == NULL) {
		printf("cas_init() error");
		return -1;
	}

	printf("cas_init() success\n");
	for (i = 0; i < 1; i++) {
		pthread_create(&tid[i], NULL, thread_write, NULL);
	}
	for (i = 0; i < 5; i++) {
		pthread_create(&tid2[i], NULL, thread_read, NULL);
	}

	sleep(40);
	cas_free();

	return 0;
}
