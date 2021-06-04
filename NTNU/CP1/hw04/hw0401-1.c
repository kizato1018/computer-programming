#include <stdio.h>
#include <stdint.h>

void Hanoi(int32_t num, int32_t from, int32_t to, int32_t spare){
	if(num == 0) return;
	Hanoi(num - 1, from, spare, to);
	printf("move disk %d to rod %d\n", num, to);
	Hanoi(num - 1, spare, to, from);
}

int main(){
	int32_t num;
	printf("Please enter the disk number (2-20): ");
	scanf("%d", &num);
	Hanoi(num, 1, 2, 3);
}