#include <stdio.h>

void print(char s[]){
	printf("%s\n",s);
}

int main(){
	char s[100];
	printf("enter your sentence: ");
	scanf("%s", s);
	printf("your sentence: ");
	print(s);
}