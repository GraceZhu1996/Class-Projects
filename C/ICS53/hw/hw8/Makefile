SERVERS = cp_server.c ls_server.c
CLIENTS = cp_client.c ls_client.c
all: servers clients

servers: $(SERVERS)
	gcc ls_server.c -o ls_server
	gcc cp_server.c -o cp_server
	
clients: $(CLIENTS)
	gcc ls_client.c -o ls_client
	gcc cp_client.c -o cp_client

clean:
	rm ls_server cp_server ls_client ls_server
