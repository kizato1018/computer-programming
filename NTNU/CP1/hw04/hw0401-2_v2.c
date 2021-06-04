#include <stdio.h>
#include <stdint.h>

int32_t rod[3][21] = {{1000}, {1000}, {1000}};
int32_t top[3] = {0};

void put(int32_t a, int32_t b) {
	if(rod[a][top[a]] > rod[b][top[b]]) {
		rod[a][++top[a]] = rod[b][top[b]];
		printf("move disk %d to rod %d\n", rod[b][top[b]--], a + 1);
	}
	else {
		rod[b][++top[b]] = rod[a][top[a]];
		printf("move disk %d to rod %d\n", rod[a][top[a]--], b + 1);
	}
}

int main(){
	int32_t number = 0, from = 0, to = 1;
	printf("Please enter the disk number (2-20): ");
	scanf("%d", &number);
	if(number < 2 || number > 20)
		printf("wrong input\n");
	for(int32_t i = 1; i <= number; i++)
		rod[0][i] = number - i + 1;
	top[0] = number;
	while(1) {
		rod[to][++top[to]] = rod[from][top[from]--];
		printf("move disk 1 to rod %d\n", to + 1);
		if(rod[to][1] == number && top[to] == number) break;
		put((1 + to) % 3, (2 + to) % 3);
		from = to;
		to = (to + 1) % 3;
	}
}