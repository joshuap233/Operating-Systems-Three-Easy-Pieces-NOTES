
#FLAGS = -pthread -g -w
FLAGS = -pthread -g

main: main.o linkList.o
	gcc main.o linkList.o $(FLAGS) -o main

main.o: main.c linkList.h
	gcc -c main.c $(FLAGS)

linkList.o: linkList.c linkList.h ../Pthread.h
	gcc -c linkList.c $(FLAGS)

clean:
	-rm linkList.o main.o main