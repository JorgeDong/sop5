#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <libsem.h>
							
#define CICLOS 10

char *pais[3]={"Peru","Bolvia","Colombia"};

SEMAPHORE exmut;

void *hilo1(void *arg)
{
	int *mynum=(int *) arg;
	int i=*mynum;

	int k;
	int l;

	for(k=0;k<CICLOS;k++)
	{
		waitsem(&exmut);
		
		// Inicia sección Crítica
		printf("Entra %s",pais[i]);
		fflush(stdout);
		usleep(rand()%1000000);
		printf("- %s Sale\n",pais[i]);
		// Termina sección Crítica
		
		signalsem(&exmut);		
		
		// Espera aleatoria fuera de la sección crítica
		usleep(rand()%1000000);
	}
}

int main()
{
	pthread_t tid[3];
	int res;
	int args[3];
	int i;
	void *thread_result;

	srand(getpid());
	
	initsem(&exmut,1);

	// Crea los hilos
	for(i=0;i<3;i++)
	{
		args[i]=i;
		res = pthread_create(&tid[i], NULL, hilo1, (void *) &args[i]);
	}

	// Espera que terminen los hilos
	for(i=0;i<3;i++)
		res = pthread_join(tid[i], &thread_result);

}


