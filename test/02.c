#include <stdio.h>

void print(char a[][10]){
	for(int i = 0; i < 3; i++){
		printf("%s\n", a[i]);
		a[i][i] = '!';
	}
}

int main(){
	char s[10][10] = {"abc", "123", "00000"};
	print(s);
	print(s);
}