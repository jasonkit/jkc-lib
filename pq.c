#include <stdlib.h>
#include <sys/types.h>
#include "pq.h"

// return ptr to queue in normal case, NULL ptr in fail case
pq* pq_create(size_t size, size_t element_size, int (*cmp)(void*, void*))
{
	pq* queue = (pq*)malloc(sizeof(pq));
	
	if (queue) {
		queue->heap = malloc(size*element_size);
		if (queue->heap) {
			queue->len = 0;
			queue->size = size;
			queue->cmp = cmp;
		}else{
			free(queue);
			queue = NULL;
		}
	}else {
		queue = NULL;
	}

	return queue;
}

void pq_delete(pq* queue)
{
	free(queue->heap);
	free(queue);
}

int pq_isFull(pq* queue)
{
	return (queue->len == queue->size);
}

// return length of queue after adding new item, -1 if the queue is full
int pq_enqueue(pq* queue, void* node)
{
	if (pq_isFull(queue))
		return -1;

	queue->heap[queue->len] = node;
	
	// bubble up
	int idx = queue->len;
	while (idx > 0) {
		int parent_idx = (idx&0x1)?(idx>>1):((idx>>1)-1);
		if (queue->cmp(queue->heap[parent_idx], queue->heap[idx]) > 0) {
			void* tmp = queue->heap[parent_idx];
			queue->heap[parent_idx] = queue->heap[idx];
			queue->heap[idx] = tmp;
			idx = parent_idx;
		}else{
			break;
		}
	}

	queue->len++;

	return queue->len;		
}

// return ptr to item to dequeue, NULL ptr if queue is empty
void* pq_dequeue(pq* queue)
{
	if (queue->len == 0)
		return NULL;
	
	void* node_to_remove = queue->heap[0];
	queue->heap[0] = queue->heap[queue->len-1];
	
	// bubble down
	int idx = 0;
	while (idx < queue->len) {
		int left = (idx<<1)+1;	
		int right = (idx<<1)+2;	
		int child = 0;

		if (right >= (queue->len-1)) {
			if (left >= (queue->len-1)) {
				break;
			} else {
				child = left;
			}
		} else {	
			if (queue->cmp(queue->heap[left], queue->heap[right]) < 0) {
				child = left;
			} else {
				child = right;
			}
		}
		if (queue->cmp(queue->heap[idx], queue->heap[child]) < 0) {
			break;
		}else{
			void* tmp = queue->heap[child];
			queue->heap[child] = queue->heap[idx];
			queue->heap[idx] = tmp;
			idx = child;
		}
	}

	queue->len--;

	return node_to_remove;
}
