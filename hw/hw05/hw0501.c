#include <stdio.h>
#include <stdint.h>

int main() {
	int32_t choice, c1, r1, c2, r2;
	printf("Please enter the operation choice (1: add; 2: sub; 3: mul): ");
	scanf("%d", &choice);
	printf("Please enter the size of the 1st matrix: ");
	scanf("%d %d", &c1, &r1);
	int32_t m1[c1][r1];
	for(int32_t i = 1; i <= c1; i++) {
		if(i % 10 == 1 && i != 11)
			printf("Please enter the %dst row of the 1st matrix: ", i);
		else if(i % 10 == 2 && i != 12)
			printf("Please enter the %dnd row of the 1st matrix: ", i);
		else if(i% 10 == 3 && i != 13)
			printf("Please enter the %drd row of the 1st matrix: ", i);
		else 
			printf("Please enter the %dth row of the 1st matrix: ", i);
		for(int32_t j = 1; j <= r1; j++)
			scanf("%d", &m1[i-1][j-1]);
	}
	printf("Please enter the size of the 2nd matrix: ");
	scanf("%d %d", &c2, &r2);
	int32_t m2[c2][r2];
	for(int32_t i = 1; i <= c2; i++) {
		if(i % 10 == 1 && i != 11)
			printf("Please enter the %dst row of the 2nd matrix: ", i);
		else if(i % 10 == 2 && i != 12)
			printf("Please enter the %dnd row of the 2nd matrix: ", i);
		else if(i% 10 == 3 && i != 13)
			printf("Please enter the %drd row of the 2nd matrix: ", i);
		else 
			printf("Please enter the %dth row of the 2nd matrix: ", i);
		for(int32_t j = 1; j <= r2; j++)
			scanf("%d", &m2[i-1][j-1]);
	}
	switch(choice) {
		case 1:
		case 2:
			if(c1 != c2 || r1 != r2) {
				printf("invalid input!\n");
				break;
			}
			printf("Answer:\n");
			for(int32_t i = 0; i < c1; i++) {
				for(int32_t j = 0; j < r1; j++) {
					printf("%d ", m1[i][j] + m2[i][j] * (choice * -2 + 3));
				}
				puts("");
			}
			break;
		case 3:
			if(r1 != c2) {
				printf("invalid input!\n");
				break;
			}
			printf("Answer:\n");
			for(int32_t i = 0; i < c1; i++) {
				for(int32_t j = 0; j < r2; j++) {
					int32_t value = 0;
					for(int32_t k = 0; k < r1; k++) {
						value += m1[i][k] * m2[k][j];
					}
					printf("%d ", value);
				}
				puts("");
			}

	}
}