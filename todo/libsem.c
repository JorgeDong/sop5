#include <pthread_utils.h>
#include <libsem.h>

// Macro que incluye el código de la instrucción máquina xchg
#define atomic_xchg(A,B) 	__asm__ __volatile__(	\
							"   lock xchg %1,%0 ;\n"	\
							: "=ir"  (A)			\
							: "m"  (B), "ir" (A)		\
							);

int g=0;


void initsem(SEMAPHORE *s,int val)
{
	s->count=val;
	initqueue(&s->queue);
}


void waitsem(SEMAPHORE *s)
{
	//GARANTIZAR ATOMICIDAD - implica que dos hilos no ejectuten wait() y signal() al mismo tiempo.
	int l=1; //variable local para cada uno de los hilos
	do{ atomic_xchg(l,g)}while(l==1);

	s->count--;//Decrementa el numero de hilos que pueden ejecutar wait sin que se bloqueen.
	if(s->count<0){
		enqueue(&s->queue,pthread_self());//Poner este hilo en cola de bloqueados
		//Liberar variables del xchg para permitir a otros hilos ejecutar wait() y signal()
		g=0;
		l=1;
		//Bloquear este hilo
		block_thread();
	}
	//Liberar variables del xchg para permitir a otros hilos ejecutar wait() y signal()
	g=0;
	l=1;

}

void signalsem(SEMAPHORE *s)
{
	//GARANTIZAR ATOMICIDAD - implica que dos procesos no ejectuten wait() y signal() al mismo tiempo.
	int l=1; //variable local para cada uno de los procesos
	do{ atomic_xchg(l,g)}while(l==1);
	s->count++; //Modificar count para señalar que habrá un hilo menos esperando en la cola
	if(s->count<=0){
		pthread_t next=dequeue(&s->queue);//Sacamos el hilo de la cola de bloqueados (FIFO)
		unblock_thread(next);//Desbloqueamos hilo
	}
	//Liberar variables del xchg para permitir a otros hilos ejecutar wait() y signal()
	g=0;
	l=1;
}

