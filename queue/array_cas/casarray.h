#ifndef _CAS_ARRAY_H_
#define _CAS_ARRAY_H_

#include <stdint.h>

/* Lock-free queue core macro function: compare and exchange */
#define CAS(ptr, oldval, newval) \
		_val_bool_compare_and_swap(ptr, oldval, newval)

/* 
 * The lock-free queue is implemented by three indexes, which are the 
 * dequeue index, the enqueue index, and the maximum dequeue index. 
 * The dequeue index is currently reading data, and the enqueue index is 
 * currently writing data (may not be completed yet, the maximum dequeue 
 * index is not equal to the dequeue index, and the maximum dequeue index 
 * can be updated only after the writing is completed). 
 *
 * */
uint32_t global_current_dequeue;		
uint32_t global_current_enqueue;
uint32_t global_current_max_dequeue;

typedef struct _cas_node_t {
	uint8_t *data_buf;

/* Reference counter: Calculate queue size */
#ifdef _CAS_GLOBAL_COUNT
	uint32_t global_count;
#endif
} cas_node_t;

#define _CAS_ARRAY_H_
