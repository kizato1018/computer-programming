cc:=g++
tar:=main
obj:=main.o maze.o robot.o

%.o : %.cpp
	$(cc) -c $^ -o $@

all : $(obj)
	$(cc) $(obj) -o $(tar)

.PHONY:clean
clean:
	rm *.o