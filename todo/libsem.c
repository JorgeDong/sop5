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
}


void waitsem(SEMAPHORE *s)
{
}

void signalsem(SEMAPHORE *s)
{
}

