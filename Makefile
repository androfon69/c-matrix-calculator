CC=gcc
CFLAGS=-Wall -g

main.o:
	$(CC) -c -o main.o src/main.c $(CFLAGS)

list.o:
	$(CC) -c -o list.o src/list.c $(CFLAGS)

build: main.o list.o
	$(CC) -o main main.o list.o $(CFLAGS)
	rm -f *.o

clean:
	rm -f *.o main
