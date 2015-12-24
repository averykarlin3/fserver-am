make: client.o server.o
	gcc client.o -o client
	gcc server.o -o server

server.o: server.c fserver.h
	gcc server.c -c

client.o: client.c fserver.h
	gcc client.c -c

clean:
	rm server
	rm client
	rm *.o

rclient:
	./client

rserver:
	./server
