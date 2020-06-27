.PHONY: all debug contest clean

all:
	gcc -c game.c -o game.o
	gcc -c agent.c -o agent.o
	gcc -c main.c -o main.o
	gcc -c server.c -o server.o
	gcc -c client.c -o client.o
	gcc main.o agent.o game.o server.o -o Take_6
	gcc main_client.o game.o agent.o client.o -o Take_6_client
# debug: game.o agent.o
# 	gcc -c server.c -o server.o
# 	gcc -c client.c -o client.o
# 	gcc -c main.c -o main.o
# 	gcc -c main_client.c -o main_client.o
# 	gcc main.o game.o agent.o server.o -o debug_server
# 	gcc main_client.o game.o agent.o client.o -o debug_client
# contest: contest.c agent.c
# 	gcc -c
clean:
	rm *.o
