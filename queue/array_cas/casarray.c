#include <sched.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "casarray.h"

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

int cas_write(uint8_t *data)
{
	uint32_t tmp_current_read;
	uint32_t tmp_current_write;

	if (!data) { return CAS_NONE_DATA; }

	do
	{
		tmp_current_read = global_current_read;
		tmp_current_write = global_current_write;
		if ( ((tmp_current_write+1) % queue_length) == tmp_current_read )
		{
			return CAS_FULL_QUEUE;
		}
	} while(CAS(&global_current_write, tmp_current_write,
					(tmp_current_write+1) % queue_length) != TRUE);

	cas_queue[tmp_current_write].data_buf = (char *)data;

	while(CAS(&global_current_max_read, tmp_current_write,
							(tmp_current_write+1) % queue_length))
	{
		sched_yield();
	}

	return CAS_OK;
}

int cas_read(uint8_t *data)
{
	uint32_t tmp_current_read;

	do
	{
		tmp_current_read = global_current_read;
		if (tmp_current_read == global_current_max_read) {
			return CAS_READ_ERROR;
		}
	} while(CAS(&global_current_read, tmp_current_read,
					(tmp_current_read+1) % queue_length) != TRUE);

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
