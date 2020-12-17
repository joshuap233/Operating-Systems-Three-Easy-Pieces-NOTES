FLAGS = -Wall -pthread -g

clean:
	rm -f *.out

b:
	gcc barrier.c $(FLAGS)

fj:
	gcc fork-join.c $(FLAGS)

mn:
	gcc mutex-nostarve $(FLAGS)

rw:
	gcc reader-writer.c $(FLAGS)

rwn:
	gcc reader-writer-nostarve.c $(FLAGS)

r:
	gcc rendezvous.c $(FLAGS)