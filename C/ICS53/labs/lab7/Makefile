all: server client

server: server.c client_handler.o
	gcc -pthread server.c client_handler.o -o server
	
client_handler.o: client_handler.c client_handler.h
	gcc -pthread -c client_handler.c

client:
	gcc -pthread client.c -o client

clean:
	rm *.o client server
