all: socket.o
	gcc -Wall -g ./server/main.c ./libs/socket.o -o ./server/server
	gcc -Wall -g ./client/main.c ./libs/socket.o -o ./client/client
socket.o:
	gcc -Wall -g -c ./libs/socket.c -o ./libs/socket.o

clean:
	rm ./libs/socket.o ./client/client ./server/server
