.PHONY: all debug contest clean

all:
	gcc -c game.c -o game.o
	gcc -c agent.c -o agent.o
	gcc -c server.c -o server.o
	gcc -c client.c -o client.o
	gcc -c main.c -o main.o
	gcc -c main_client.c -o main_client.o
	gcc -c main_server.c -o main_server.o
	gcc -c 40847025S.c -o 40847025S.o
	gcc main.o agent.o game.o server.o -o Take_6
	gcc main_client.o game.o agent.o client.o -o Take_6_client
	gcc main_server.o game.o agent.o server.o -o Take_6_server
	
clean:
	rm *.o
