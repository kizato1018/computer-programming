//1111222233334545666
//1 2 3 4 5 6 7 8 9 12 12 12 31 31 31 34 32 -1
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool check(int32_t card[], bool p[],int32_t cnt) {
	if(cnt == 0) return 1;
	for(int32_t i = 1; i < 35; i++) {
		if(card[i] >= 3) {
			card[i] -= 2;
			p[i] = 1;
			return check(card, p, cnt-3);
		}
		else if(i < 8 || (i > 9 && i < 17) || (i > 18 && i < 26)) {
			if(card[i+1] > 0 && card[i+2] > 0) {
				for(int32_t j = 0; j < 3; card[j++]--);
				return check(card, p, cnt-3);
			}
		}
		else if(p[i]) {
			card[i]--;
			return check(card, p, cnt-1);
		}
	}
	return 0;
}

int main() {
	int32_t card[35] = {0};
	bool p[35] = {0};
	int32_t cnt = 0, in;
	while(1) {
		printf("Please enter the tile: ");
		scanf("%d", &in);
		if(in == -1) break;
		else if(in < 1 || in > 34){
			printf("Wrong input\n");
			return 0;
		}
		else {
			card[in]++;
			if(card[in] > 4){
				printf("Cheating!\n");
				return 0;
			}
			cnt++;
		}
	}
	for(int32_t i = 1; i < 35; i++) {
		if(card[i] > 2){
			card[i] -= 2;
			if(check(card, p, cnt-2)) {
				printf("Winning Hand!\n");
				return 0;
			}
			card[i] += 2;
		}
	}
	printf("Not a Winning Hand.\n");
}