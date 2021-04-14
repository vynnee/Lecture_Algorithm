#include<stdio.h>
#include <string.h>

int InitNext(char p[], int M) {
	int* next = (int*)malloc(sizeof(int) * M);
	int i, j;

	next[0] = -1;

	for (i = 0, j = -1; i < M; i++, j++) {
		if (p[i] == p[j])
			next[i] = next[j];
		else
			next[i] = j;

		while ((j >= 0) && (p[i] != p[j]))
			j = next[j];
	}
	next_print(next, M);
}

int next_print(int next[], int M) {
	int i;

	for (int i = 0; i < M; i++) {
		printf("%d ", next[i]);
	}
	printf("\n");
}

void main() {
	char p1[5] = "AABAA";
	InitNext(p1, 5);

	char p2[7] = "ABAABAB";
	InitNext(p2, 7);

	char p3[8] = "ABABABAC";
	InitNext(p3, 8);

	printf("12181785 ¼­Çýºó\n");
}