CC = gcc
AR = ar
CFLAGS = -Wall -Werror

all: connections


connections: main.o
	${CC} ${CFLAGS} -o connections main.o

main.o: main.c
	${CC} ${CFLAGS} -c main.c

clean:
	rm -f *.a *.o connections