#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define N 10

typedef struct Student {
	int id;
	int Chinese;
	int Math;
	int English;
}student;

bool cmp(student a, student b, bool order) { // methood =0 greater, =1 less
	bool r;
	if(a.Chinese > b.Chinese) r = 1;
	else if(b.Chinese > a.Chinese) r = 0;
	else {
		if(a.Math > b.Math) r = 1;
		else if(b.Math > a.Math) r = 0;
		else {
			if(a.English > b.English) r = 1;
			else if(b.English > a.English) r = 0;
			else r = 0;
		}
	}
	if(order) return !r;
	return r;

}

void swap(student *a, student *b) {
	student tmp = *a;
	*a = *b;
	*b = tmp;
}

void sort(student * const s, int n, bool order) {
	for(int i = 0; i < n; i++) {
		for(int j = 1; j < n; j++) {
			if(cmp(*(s+j-1), *(s+j), order))
				swap(s+j-1, s+j);
		}
	}
}

void init(student *s, int n){
	srand(time(NULL));
	for(int i = 0; i < n; i++) {
		s[i].id = i+1;
		s[i].Chinese = rand() % 101;
		s[i].Math = rand() % 101;
		s[i].English = rand() % 101;
	}

}

int main() {

	student s[N] = {0};
	init(s, N);
	sort(s, N, 0);
	printf("order by ascending\n");
	for(int i = 0; i < N; i++) {
		printf("%d: Chinese:%d Math:%d English:%d\n", s[i].id, s[i].Chinese, s[i].Math, s[i].English);
	}
	printf("order by descending\n");
	sort(s, N, 1);
	for(int i = 0; i < N; i++) {
		printf("%d: Chinese:%d Math:%d English:%d\n", s[i].id, s[i].Chinese, s[i].Math, s[i].English);
	}
}