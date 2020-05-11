#include <stdio.h>
#include <stdint.h>

void b(void) {
	static int cnt = 100;
	printf("cnt: %d\n", cnt);
	--cnt;
}

int main() {
	b();
	b();
}
