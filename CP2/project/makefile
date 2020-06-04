all:
	gcc -c game.c -o game.o
	gcc -c agent.c -o agent.o
	gcc -c server.c -o server.o
	gcc -c client.c -o client.o
	gcc -c main.c -o main.o
	gcc main.o agent.o game.o -o Take_6
debug: game.o agent.o server.o client.o
	gcc -c server.c -o server.o
	gcc -c client.c -o client.o
	gcc debug_server.c server.o game.o agent.o  -o debug_server
	gcc debug_client.c client.o game.o agent.o  -o debug_client
clean:
	rm *.o