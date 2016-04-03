all: my_shell handle_signals

ioredirect.o: ioredirect.c ioredirect.h
	$(CC) -c ioredirect.c

Timer.o: Timer.c Timer.h
	$(CC) -c Timer.c

my_shell: my_shell.c ioredirect.o
	gcc my_shell.c ioredirect.o -o my_shell

handle_signals: handle_signals.c
	gcc handle_signals.c -o handle_signals

clean:
	rm ioredirect.o my_shell handle_signals
