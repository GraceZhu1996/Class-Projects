all: main.c stk.o
	gcc -ggdb -std=c99 main.c stk.o
stk.o: stk.c stk.h
	gcc -c stk.c -std=c99

clean:
	rm a.out stk.o
