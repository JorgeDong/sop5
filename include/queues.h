// #ifndef QUEUES_H

#include <pthread.h>

#define QUEUESIZE 10

typedef struct {
	pthread_t threads[QUEUESIZE];
	int entry,exit;
} QUEUE;

void enqueue(QUEUE *q,pthread_t t);
pthread_t dequeue(QUEUE *q);
void initqueue(QUEUE *q);

// #endif