CC = gcc
CCFLAGS = -ggdb
SOURCE = main.c methods.o Timer.o

all: main

methods.o: methods.c methods.h
	$(CC) -c methods.c

Timer.o: Timer.c Timer.h
	$(CC) -c Timer.c

main: $(SOURCE)
	$(CC) $(CCFLAGS) $(SOURCE) -o methods

clean:
	rm methods.o methods Timer.o
