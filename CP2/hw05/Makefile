include = -Icurl-7.70.0/include
lib = -Lcurl-7.70.0/lib/.libs

.PHONY: test
all:
	gcc hw0501.c -o hw0501
	gcc hw0502.c -o hw0502
	gcc -D DEBUG_LEVEL_NONE hw0503.c -o hw0503
	gcc $(include) $(lib) hw0504.c -o hw0504 -lcurl 
test:
	gcc $(include) $(lib) test.c -o test -lcurl 