.PHONY: all clean
all:
	gcc hw0501.c -o hw0501
	gcc hw0502.c -o hw0502
	gcc -D DEBUG_LEVEL_VVERBOSE hw0503.c -o hw0503
	gcc $(include) $(lib) hw0504.c -o hw0504 -lcurl 
	gcc hw0505.c -o hw0505
clean:
	rm hw0501 hw0502 hw0503 hw0504 hw0505