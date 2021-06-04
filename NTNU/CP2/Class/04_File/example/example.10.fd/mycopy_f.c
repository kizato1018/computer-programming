#include <stdio.h>
#define buffer_size 1024
int main() {
	FILE *fin = NULL;
	FILE *fout = NULL;
	char buffer[buffer_size] = {};
	size_t size = 0;
	fin = fopen("maldives.bmp","rb");
	if(fin == NULL) {
		printf("read error\n");
		return(1);
	}
	fout = fopen("maldives_copy.bmp", "wb");
	while(size = fread(buffer, 1, buffer_size,fin)) {
		fwrite(buffer, 1, size, fout);
	}
	fclose(fin);
	fclose(fout);
	
}
