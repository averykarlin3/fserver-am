make: client.o server.o
	gcc client.o -o client
	gcc server.o -o server

server.o: server.c fserver.h
	gcc server.c -c

client.o: client.c fserver.h
	gcc client.c -c

client: client
	./client

server: server
	./server
