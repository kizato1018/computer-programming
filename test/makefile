TAR = $(patsubst %.c, %, $(wildcard *.c)) $(patsubst %.cpp, %, $(wildcard *.cpp))

% : %.c
	gcc $< -o $@
% : %.cpp
	g++ $< -o $@

all : $(TAR)

clean : $(TAR)
	rm $(TAR)