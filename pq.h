#ifndef __JKC_LIB_PQ_H__
#define __JKC_LIB_PQ_H__

// Simple binary heap-based piority queue implementation
// To transverse the queue, one just can
//
// for (int i=0; i< pqueue->len; i++) {
//		void* item = pqueue->heap[i];
// }
//
// To dequeue the whold queue, one can
//
// while (pqueue->len) {
// 		void* item = pq_dequeue(pqueue);
// }

typedef struct
{
	void** heap;
	size_t len;
	size_t size;
	int (*cmp)(void*, void*);
} pq;

pq* pq_create(size_t size, size_t element_size, int (*cmp)(void*, void*));
void pq_delete(pq* queue);
int pq_isFull(pq* queue);
int pq_enqueue(pq* queue, void* node);
void* pq_dequeue(pq* queue);

#endif
