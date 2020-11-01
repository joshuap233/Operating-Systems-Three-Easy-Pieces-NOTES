
#FLAGS = -pthread -g -w
FLAGS = -pthread -g

main: main.o counter.o
	gcc main.o counter.o $(FLAGS) -o main

main.o: main.c counter.h
	gcc -c main.c $(FLAGS)

counter.o: counter.c counter.h ../Pthread.h
	gcc -c counter.c $(FLAGS)

clean:
	-rm counter.o main.o main