ALL=stat ls tail find
COMMON=common.c common.h

FLAGS=-Wall -g

all: $(ALL)

stat: stat.c $(COMMON)
	gcc stat.c $(COMMON) -o stat $(FLAGS)
ls: ls.c $(COMMON)
	gcc ls.c $(COMMON) -o ls $(FLAGS)
tail: tail.c
	gcc tail.c -o tail $(FLAGS)
find: find.c $(COMMON)
	gcc find.c $(COMMON) -o find $(FLAGS)

clean:
	rm $(ALL)