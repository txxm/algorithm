#include <sched.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "casarray.h"

/* 
 * Initialization: The user can customize the queue length. If size is 0,
 * it means that the default length of the queue is enabled.
 */
void *cas_init(uint32_t size)
{
	if (!size) {
		queue_length = _QUEUE_DEFAULT_SIZE;
	} else {
		queue_length = size;
	}
	cas_queue = (cas_node_t *) malloc(sizeof(cas_node_t)*queue_length);
	if (!cas_queue) {
		return NULL;
	}

	return cas_queue;
}

/* Producer */
int cas_write(uint8_t *data)
{
	uint32_t tmp_current_read;
	uint32_t tmp_current_write;

	if (!data) { return CAS_NONE_DATA; }

	/* Update the producer's index: the index value of the data
	 * to be written. 
	 * */
	do
	{
		/* Since the temporary production and temporary consumption
		 * indexes are not atomic operations, when the length of the data
		 * that can be consumed in the current queue is obtained, the
		 * current reading index cannot be subtracted from the maximum
		 * consumption index, and can be counted by the cas_global_count
		 * counter in casarray.h, but the performance will be Reduced. 
		 */
		tmp_current_read = global_current_read;
		tmp_current_write = global_current_write;
		if ( ((tmp_current_write+1) % queue_length) == tmp_current_read )
		{
			return CAS_FULL_QUEUE;
		}
	} while(CAS(&global_current_write, tmp_current_write,
					(tmp_current_write+1) % queue_length) != TRUE);

	/* Write data to the space corresponding to the index */
	cas_queue[tmp_current_write].data_buf = (char *)data;

	/* Update the largest index that can currently be consumed: Ensure
	 * that the producer is not updated until production is complete,
	 * and that there must be multiple producers that must be updated
	 * in order.
	 */
	while(CAS(&global_current_max_read, tmp_current_write,
							(tmp_current_write+1) % queue_length))
	{
		/* Proactively give up the CPU and let the front-end producer
		 * update the current maximum read index value
		 */
		sched_yield();
	}

	return CAS_OK;
}

/* Consumer */
int cas_read(uint8_t *data)
{
	uint32_t tmp_current_read;

	/* 
	 * Update consumer index: find an index that can currently read data.
	 */
	do
	{
		tmp_current_read = global_current_read;
		if (tmp_current_read == global_current_max_read) {
			return CAS_READ_ERROR;
		}
	} while(CAS(&global_current_read, tmp_current_read,
					(tmp_current_read+1) % queue_length) != TRUE);

	/* The consumer takes the data from the queue and places it
	 * in the user buffer. 
	 */
	memcpy(data, cas_queue[tmp_current_read].data_buf,
					strlen(cas_queue[tmp_current_read].data_buf));

	return CAS_OK;
}

void cas_free()
{
	while (1)
	{
		if (CAS(&cas_free_count, 0, 1) == TRUE)
		{
			free(cas_queue);
			return ;
		}
		if (cas_free_count) {
			return ;
		}
		usleep(10);
	}
}


/*
 * Returns the parsing corresponding to the error code
 */
char *cas_strerror(int error_code)
{
	switch (error_code)
	{
		case CAS_OK:
			return "ok\n";
		case CAS_NONE_DATA:
			return "invalid data\n";
		case CAS_FULL_QUEUE:
			return "queue is full\n";
		case CAS_EMPTY_QUEUE:
			return "queue is empty\n";
		case CAS_READ_ERROR:
			return "write queue failed\n";
		case CAS_WRITE_ERROR:
			return "read queue failed\n";
	}

	return "invalid error code\n";
}
