#include <queues.h>
typedef struct {
	int count;
	QUEUE queue;
} SEMAPHORE;

void initsem(SEMAPHORE *s,int val);
void waitsem(SEMAPHORE *s);
void signalsem(SEMAPHORE *s);
