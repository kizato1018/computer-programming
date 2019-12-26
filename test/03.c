#include <stdio.h>
#include <stdlib.h>

int main(){
	unsigned int n;
	scanf("%d", &n);
	int *a = malloc(n * sizeof(int));
	for(int i = 0; i < n; i++){
		a[i] = n - i;
	}
	for(int i = 0; i < n; i++){
		printf("a[%d]: %d\n", i, a[i]);
	}
}