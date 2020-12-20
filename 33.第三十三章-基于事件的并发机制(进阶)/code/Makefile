FLAGS = -g -Wall -pthread

all: socket socket-select socket-select-file

socket: socket.c common.h
	gcc socket.c common.c $(FLAGS) -o socket

socket-select: socket-select.c common.h
	gcc socket-select.c common.c -o socket-select $(FLAGS)

socket-select-file: socket-select-file.c common.h
	gcc socket-select-file.c common.c -o socket-select-file $(FLAGS)

clean:
	-rm socket socket-select