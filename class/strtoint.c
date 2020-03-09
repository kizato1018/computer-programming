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
		if(str[i] >= '0' && str[i] <= '9') // -15 15 
			result = result * 10 + str[i] - '0';
		else {
			*error = 1;
			return 0;
		}
		i++;
	}
	return result * sign;
}

int32_t hexstr_to_int(char *str, int32_t *error) {
	int32_t i = 0;
	uint32_t result = 0;
	while(str[i]) {
		if(str[i] >= '0' && str[i] <= '9')
			result = result * 16 + str[i] - '0';
		else if(str[i] >= 'a' && str[i] <= 'z')
			result = result * 16 + str[i] - 'a' + 10;
		else if(str[i] >= 'A' && str[i] <= 'Z')
			result = result * 16 + str[i] - 'A' + 10;
		else {
			*error = 1;
			return 0;
		}
		if(++i > 8) {
			*error = 2;
			return 0;
		}
	}
	return (int32_t)result;
}

int main() {
	char *string;
	int32_t number = 0;
	int32_t error = 0;
	printf("Please enter a number(hex): ");
	scanf("%s", string);
	//number = str_to_int(string, &error);
	number = hexstr_to_int(string, &error);
	switch(error) {
		case 1:
			printf("wrong input\n");
			return 0;
		case 2:
			printf("out of range to int32_t\n");
			return 0;
	}
	printf("number: %d\n", number);
}