
#FLAGS = -pthread -g -w
FLAGS = -pthread -g

main: main.o queue.o
	gcc main.o queue.o $(FLAGS) -o main

main.o: main.c queue.h
	gcc -c main.c $(FLAGS)

queue.o: queue.c queue.h ../Pthread.h
	gcc -c queue.c $(FLAGS)

clean:
	-rm queue.o main.o main