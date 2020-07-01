.PHONY: map player game test

all:
	g++ -c map_unit.cpp -o map_unit.o
	g++ -c player.cpp -o player.o
	g++ -c game.cpp -o game.o
	g++ -c main.cpp -o main.o
	g++ main.o game.o map_unit.o player.o -o Monopoly
map:
	g++ -c map_unit.cpp -o map_unit.o
player:
	g++ -c player.cpp -o player.o
game:
	g++ -c game.cpp -o game.o
main:
	g++ -c main.cpp -o main.o
test:
	g++ test.cpp map_unit.o -o test
clean:
	rm *.o test