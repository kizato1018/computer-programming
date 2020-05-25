TAR = $(patsubst %.c, %, $(wildcard *.c)) $(patsubst %.cpp, %, $(wildcard *.cpp))

% : %.c
	gcc $< -o $@
% : %.cpp
	g++ $< -o $@

all : $(TAR)
.PHONY:clean
clean : $(TAR)
	rm $(TAR)
