#include <stdio.h>
#include <string.h>
#define END {puts("invalid"); return 0;}

int convert(const char *s) {
	if(strlen(s) < 2) return -1;
	else if(strlen(s) >= 3 && s[2] != '\n') return -1;
	int v = 0;
	for(int i = 0; i < 2; i++) {
		if(s[i] >= '0' && s[i] <= '9')
			v += (s[i] - '0') * ((i) ? 1 : 16);
		else if(s[i] >= 'A' && s[i] <= 'F')
			v += (s[i] - 'A' + 10) * ((i) ? 1 : 16);
		else if(s[i] >= 'a' && s[i] <= 'f')
			v += (s[i] - 'a' + 10) * ((i) ? 1 : 16);
		else return -1;

	}
	return v;
}

int main() {
	char a[20] = {0};
	int mac[6] = {0};
	char *token;
	printf("Please enter the string: ");
	if(strlen(a) > 18  || strlen(a) < 17) END
	if(strlen(a) == 18 && a[17] != '\n') END
	token = strtok(a, ":");
	for(int i = 0; i < 6; i++) {
		if(token == NULL) END
		mac[i] = convert(token);
		if(mac[i] < 0) END
		token = strtok(NULL, ":");
	}
	if(token != NULL) END
	for(int i = 0; i < 6; i++)
		printf("%02x%c", mac[i], "-\n"[i==5]);
	
}
