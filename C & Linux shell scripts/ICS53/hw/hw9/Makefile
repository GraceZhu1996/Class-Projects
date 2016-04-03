# Note, you must change the port to your unique port number (between 1000 and 2^16-1) based on your Student ID
PORT = 7945
HOST = odin
PROGRAMS = server client tpr_server tp_server lf_server Timer.o
S = -std=c99 -ggdb

#Thread Per Request
tpr_server: tpr_server.c
	gcc $S tpr_server.c -lpthread -o tpr_server

#Thread Pool
tp_server: tp_server.c
	gcc $S tp_server.c -lpthread -o tp_server

#Leader-Follower Server
lf_server: lf_server.c
	gcc $S lf_server.c -lpthread -o lf_server

client: client.c Timer.o
	gcc $S client.c Timer.o -lpthread -o client

Timer.o: Timer.c Timer.h
	gcc $S -c Timer.c

#TESTING
call_tpr: tpr_server
	tpr_server $(PORT) &
	echo Starting client

call_tp: tp_server
	tp_server $(PORT) &
	echo Starting client

call_lf: lf_server
	lf_server $(PORT) &
	echo Starting client

call_client: client
	client $(HOST) $(PORT)
	ls -lr Thread_*
	du

#test: call_lf call_client

clean:
	/bin/rm -rf $(PROGRAMS) Thread_*
