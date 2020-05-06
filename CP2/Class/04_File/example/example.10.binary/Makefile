all: bmp_read_v1.c bmp_read_v2.c bmp_read_v2_error.c bmp_write.c
	gcc bmp_read_v1.c -o bmp_read_v1
	gcc bmp_read_v2.c -o bmp_read_v2
	gcc bmp_read_v2_error.c -o bmp_read_v2_error
	gcc bmp_write.c -o bmp_write
	gcc bmp_write_gray.c -o bmp_write_gray
	gcc bmp_write_RGB.c -o bmp_write_RGB
clean:
	rm -rf bmp_read_v1
