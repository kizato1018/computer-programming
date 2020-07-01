.PHONY: map player game test

all:
	g++ -c map_unit.cpp -o map_unit.o
	g++ -c player.cpp -o player.o
	g++ -c game.cpp -o game.o
	g++ -c main.cpp -o main.o
	g++ main.o game.o map_unit.o player.o -o RichMini
map: map_unit.cpp map_unit.h
	g++ -c map_unit.cpp -o map_unit.o
player: player.cpp player.h
	g++ -c player.cpp -o player.o
game: game.cpp game.h
	g++ -c game.cpp -o game.o
main: main.cpp
	g++ -c main.cpp -o main.o
test: test.cpp
	g++ test.cpp map_unit.o -o test
clean:
	rm *.o test