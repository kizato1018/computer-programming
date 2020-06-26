.PHONY: all debug contest clean

all:
	gcc -c game.c -o game.o
	gcc -c agent.c -o agent.o
	gcc -c main.c -o main.o
	gcc -c server.c -o server.o
	gcc -c client.c -o client.o
	gcc main.o agent.o game.o server.o -o Take_6
debug: game.o agent.o
	gcc -c server.c -o server.o
	gcc -c client.c -o client.o
	gcc debug_server.c game.o agent.o server.o -o debug_server
	gcc debug_client.c game.o agent.o client.o -o debug_client
contest: contest.c agent.c
	gcc -c
clean:
	rm *.o
