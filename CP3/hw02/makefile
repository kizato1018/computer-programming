cc:=g++
tar:=main
obj:=main.o

%.o : %.cpp
	$(cc) -c $^ -o $@

all : $(obj)
	$(cc) $(obj) -o $(tar)

.PHONY:clean
clean:
	rm *.o