#include <stdio.h>
#include <stdint.h>

int32_t str_to_int(char *str, int32_t *error) {
	int32_t i = 0;
	int32_t result = 0;
	int32_t sign = 1;
	if(str[i] == '-') {
		sign = -1;
		i++;
	}
	while(str[i]) {
		result *= 10;
		if(str[i] >= '0' && str[i] <= '9') // -15 15 
			result += str[i] - '0';
		else {
			*error = 1;
			return 0;
		}
		i++;
	}
	return result * sign;
}

int main() {
	char *string;
	int32_t number = 0;
	int32_t error = 0;
	printf("Please enter a number: ");
	scanf("%s", string);
	number = str_to_int(string, &error);
	if(error) {
		printf("wrong input\n");
		return 0;
	}
	printf("number: %d\n", number);
}
