FLAGS = -g -Wall -pthread

all: socket socket-select

socket: socket.c common.h
	gcc socket.c $(FLAGS) -o socket

socket-select: socket-select.c common.h
	gcc socket-select.c -o socket-select $(FLAGS)

clean:
	-rm socket socket-select