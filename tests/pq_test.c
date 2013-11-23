#include "stdio.h"
#include <stdlib.h>
#include "pq.h"
#include <assert.h>

int cmp(void* a, void* b)
{
	return (int)a-(int)b;
}

int main ()
{
	srand(1023);
	pq* queue = pq_create(100,sizeof(int),cmp);

	long i;
	for(i=0; i<37; i++) {
		pq_enqueue(queue, (void*)(long)(rand()&0xff));
	}
	
	int last = (int)pq_dequeue(queue);
	while(queue->len>10) {
		int cur = (int)pq_dequeue(queue);
		assert(cur >= last);
	}

	for(i=0; i<26; i++) {
		pq_enqueue(queue, (void*)(long)(rand()&0xff));
	}
	
	last = (int)pq_dequeue(queue);
	while(queue->len) {
		int cur = (int)pq_dequeue(queue);
		assert(cur >= last);
	}

	pq_delete(queue);
	printf("PASSED\n");
	return 0;
}
