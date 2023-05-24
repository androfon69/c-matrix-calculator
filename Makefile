CC = gcc
CFLAGS = -Wall -g
DEPS = include/list.h include/matrix.h

main: matrix.o list.o main.o
	$(CC) -o main matrix.o list.o main.o $(CFLAGS)
	rm -f *.o

main.o: src/main.c $(DEPS)
	$(CC) -c -o main.o src/main.c $(CFLAGS)

matrix.o: src/matrix.c $(DEPS)
	$(CC) -c -o matrix.o src/matrix.c $(CFLAGS)

list.o: src/list.c $(DEPS)
	$(CC) -c -o list.o src/list.c $(CFLAGS)

run: main
	./main

clean:
	rm -f *.o main