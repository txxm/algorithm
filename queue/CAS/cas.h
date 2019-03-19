#ifndef _CAS_H_
#define _CAS_H_

#include <stdint.h>

#define ERR_CAS_DELETE	"no elements to delete"
#define ERR_CAS_EMPTY	"the queue is empty"

#define TRUE	!(0)
#define FALSE	0
#define CAS(tail, q, p)		__sync_bool_compare_and_swap(tail, q, p)

int count = 0;

typedef struct node_t {
	char *data;
	struct node_t *next;
} node_t;

typedef struct queue_t {
	struct node_t *head;
	struct node_t *tail;
} queue_t;

void *cas_init(queue_t *queue);
void *cas_add(queue_t *queue, char *value);
void *cas_delete(queue_t *queue, node_t *p);
void *cas_strerror(char *error);
void cas_free(node_t *p);

#endif /* _CAS_H_ */
