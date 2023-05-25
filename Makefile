CC = gcc
CFLAGS = -Wall -g -lm
DEPS = include/list.h include/matrix.h include/commands.h include/operations.h
OBJS = matrix.o list.o commands.o operations.o main.o

main: matrix.o list.o main.o commands.o operations.o
	$(CC) -o main $(OBJS) $(CFLAGS)
	rm -f *.o

main.o: src/main.c $(DEPS)
	$(CC) -c -o main.o src/main.c $(CFLAGS)

operations.o: src/operations.c $(DEPS)
	$(CC) -c -o operations.o src/operations.c $(CFLAGS)

matrix.o: src/matrix.c $(DEPS)
	$(CC) -c -o matrix.o src/matrix.c $(CFLAGS)

list.o: src/list.c $(DEPS)
	$(CC) -c -o list.o src/list.c $(CFLAGS)

commands.o: src/commands.c $(DEPS)
	$(CC) -c -o commands.o src/commands.c $(CFLAGS)

run: main
	./main

clean:
	rm -f *.o main