#include <pthread.h>
#include <queues.h>

pthread_t unblock_t=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

void block_thread()
{
	pthread_t i=pthread_self();
	pthread_mutex_lock(&mutex);
	while(unblock_t!=i)
		pthread_cond_wait(&cond,&mutex);
	unblock_t=0;
	pthread_mutex_unlock(&mutex);

}

void unblock_thread(pthread_t t)
{
	pthread_mutex_lock(&mutex);
	unblock_t=t;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
}

