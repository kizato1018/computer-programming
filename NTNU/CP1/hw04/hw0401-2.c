#include <stdio.h>
#include <stdint.h>
#include <math.h>

int32_t rod[3][20] = {0};

int32_t Top (int n){
	int i = 0;
	while(rod[n][i]) i++;
	if(i > 0)
		return rod[n][i-1];
	else
		return 1000;
}
int32_t Pop(int n){
	int i = 0, r;
	while(rod[n][i]) i++;
	if(i > 0){
		r = rod[n][i-1];
		rod[n][i-1] = 0;
	}
	return r;
}

void Push(int to, int disk){
	int i = 0;
	while(rod[to][i]) i++;
	rod[to][i] = disk;
	printf("move disk %d to rod %d\n", disk, to+1);
}

int main(){
	int32_t n;
	int32_t cnt = 0;
	printf("Please enter the disk number (2-20): ");
	scanf("%d", &n);
	for(int32_t i = 0, j = n; i < n; i++){
		rod[0][i] = j--;
	}
	if(n % 2){
		while(cnt < pow(2, n) - 1){
			switch(cnt % 3){
				case 0:
					(Top(0) < Top (1)) ? Push(1, Pop(0)) : Push(0, Pop(1));
					break;
				case 1:
					(Top(0) < Top (2)) ? Push(2, Pop(0)) : Push(0, Pop(2));
					break;
				case 2:
					(Top(1) < Top (2)) ? Push(2, Pop(1)) : Push(1, Pop(2));
					break;
			}
			cnt++;
		}
	}
	else{
		while(cnt < pow(2, n) - 1){
			switch(cnt % 3){
				case 0:
					(Top(0) < Top (2)) ? Push(2, Pop(0)) : Push(0, Pop(2));
					break;
				case 1:
					(Top(0) < Top (1)) ? Push(1, Pop(0)) : Push(0, Pop(1));
					break;
				case 2:
					(Top(1) < Top (2)) ? Push(2, Pop(1)) : Push(1, Pop(2));
					break;
			}
			cnt++;
		}
	}

}