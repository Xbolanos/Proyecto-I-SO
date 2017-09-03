
output: server.o  thread.o client.o 
	gcc server.o -o server
	gcc client.o -o client
	gcc -pthread -o thread thread.o


server.o: server.c
	gcc -c server.c

client.o: client.c
	gcc -c client.c

thread.o: thread.c
	gcc -c thread.c	

clean:
	rm *.o client server thread