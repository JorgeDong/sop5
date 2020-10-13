I=include
B=bin
S=sources
L=lib
T=todo

all: $B/example

$B/example: $S/example.c $L/pthread_utils.o $L/libsem.o $T/libsem.h $L/queues.o
	gcc -o $B/example $S/example.c $L/pthread_utils.o $L/queues.o $L/libsem.o -pthread -I$I -I$T
	
$L/pthread_utils.o: $S/pthread_utils.c
	gcc -o $L/pthread_utils.o -c $S/pthread_utils.c -I$I
	
$L/libsem.o: $T/libsem.c $T/libsem.h
	gcc -o $L/libsem.o -c $T/libsem.c -I$I -I$T
	
$L/queues.o: $S/queues.c $I/queues.h
	gcc -o $L/queues.o -c $S/queues.c -I$I
	
clean:
	rm $B/example $L/*.o