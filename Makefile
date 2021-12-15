CC = gcc
AR = ar
CFLAGS = -Wall -Werror

all: stringProg


stringProg: main.o
	${CC} ${CFLAGS} -o stringProg main.o

main.o: main.c
	${CC} ${CFLAGS} -c main.c

clean:
	rm -f *.a *.o stringProg