#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cas.h"

void *cas_init(queue_t *queue)
{
	queue->head = queue->tail = malloc(sizeof(node_t));
	if (!queue->head) {return NULL;}

	queue->head->data = queue->tail->data = NULL;
	return queue;
}

/*
void *cas_add(queue_t *queue, char *value)
{
	node_t *p, *q;
	if (!queue) {return NULL;}

	p = malloc(sizeof(node_t));
	if (!p) {return NULL;}
	memcpy(p->data, value, strlen(value));
	p->next = NULL;

	do
	{
		q = queue->tail;
	} while(CAS(&q->next, NULL, p) != TRUE); // 线程死掉，不会更新尾指针，其他线程一直循环
	CAS(&queue->tail, q, p);

	return queue;
}
*/

void *cas_add(queue_t *queue, char *value)
{
	node_t *p, *q, *oldq;
	if (!queue) {return NULL;}

	p = malloc(sizeof(node_t));
	if (!p) {return NULL;}
	memcpy(p->data, value, strlen(value));
	p->next = NULL;

	q = queue->tail;
	oldq = q;
	do
	{
		if (q->next != NULL) {
			q = q->next; /* 指针自己移动到尾部 */
		}
	} while(&q->next, NULL, p);
	CAS(&queue->tail, oldq, p);
}

void *cas_delete(queue_t *queue, node_t *p)
{
	if (!queue) {return NULL;}

	do
	{
		p = queue->head;
		if (p->next == NULL) {return NULL;}
	} while(CAS(&queue->head, p, p->next));

	return p;
}

void cas_empty(queue_t *queue)
{
	node_t p, *q;
	if (!queue) {return ;}

	q = cas_delete(queue, &p);
	cas_free(queue->head);
}

void cas_free(node_t *p)
{
	if (__sync_fetch_and_add(&count, 1) == 1) {
		if (!p) {
			free(p);
		}
		__sync_lock_release(&count, 0);
	}
}

void *cas_strerror(char *error)
{
	return error;
}
