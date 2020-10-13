#include <queues.h>

void enqueue(QUEUE *q,pthread_t t)
{
	q->threads[q->entry]=t;
	q->entry++;
	q->entry%=QUEUESIZE;
}

pthread_t dequeue(QUEUE *q)
{
	pthread_t ret=q->threads[q->exit];
	q->exit++;
	q->exit%=QUEUESIZE;
	return(ret);
}

void initqueue(QUEUE *q)
{
	q->entry=0;
	q->exit=0;
}

