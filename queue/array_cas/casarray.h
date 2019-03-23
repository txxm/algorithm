#ifndef _CAS_ARRAY_H_
#define _CAS_ARRAY_H_

#include <stdint.h>

#define TRUE	!(0)
#define FALSE	0

#ifndef _QUEUE_MAX_SIZE
#define _QUEUE_MAX_SIZE 	1024
#endif
#ifndef _QUEUE_MIN_SIZE
#define _QUEUE_MIN_SIZE 	8
#endif
#ifndef _QUEUE_DEFAULT_SIZE
#define _QUEUE_DEFAULT_SIZE 128
#endif

#define CAS_OK				0
#define CAS_NONE_DATA		1
#define CAS_FULL_QUEUE		2
#define CAS_EMPTY_QUEUE		3
#define CAS_WRITE_ERROR		4
#define CAS_READ_ERROR		5

/* Reference counter: Calculate queue size */
#ifdef _CAS_GLOBAL_COUNT
	uint32_t cas_global_count;
#endif

/* Lock-free queue core macro function: compare and exchange */
#define CAS(ptr, oldval, newval) \
		__sync_bool_compare_and_swap(ptr, oldval, newval)

/* Release the counter of the dynamic array */
#ifndef _CAS_FREE_COUNT
#define _CAS_FREE_COUNT
uint32_t cas_free_count;
#endif

/* The lock-free queue is implemented by three indexes, which are the 
 * dequeue index, the enqueue index, and the maximum dequeue index. 
 * The dequeue index is currently reading data, and the enqueue index is 
 * currently writing data (may not be completed yet, the maximum dequeue 
 * index is not equal to the dequeue index, and the maximum dequeue index 
 * can be updated only after the writing is completed). 
 */
uint32_t global_current_write;
uint32_t global_current_read;		
uint32_t global_current_max_read;

typedef struct _cas_node_t {
	char *data_buf;
} cas_node_t;

uint32_t queue_length;
extern cas_node_t *cas_queue;

void *cas_init(uint32_t size);
int cas_read(uint8_t *data);
int cas_write(uint8_t *data);
void cas_free();
char *cas_strerror(int error_code);

#endif /*_CAS_ARRAY_H_ */
