#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define N 100000
#define TRUE 1
#define FALSE 0

int main() {
	int i, a[N];
	double start_time;

	srand(time(NULL));
	for (i = 0; i < N; i++) {
		a[i] = rand() % 100;
	}

	for (i = 0; i < N; i++) {
		printf("%d ", a[i]);
	}

	return 0;
}