.PHONY: all clean
all:
	gcc fin01.c -o fin01
	gcc fin02.c -o fin02
	gcc -c fin03.c -o fin03.o
	gcc test.c fin03.o -o fin03
clean:
	rm fin01 fin02 fin03 fin03.o