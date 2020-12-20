FLAGS = -Wall
ALL = check-xor check-fletcher

all: $(ALL)

check-fletcher:check-fletcher.c common.h
	gcc $(FLAGS) -o check-fletcher check-fletcher.c

check-xor: check-xor.c common.h
	gcc $(FLAGS) -o check-xor check-xor.c

clean:
	-rm  $(ALL)