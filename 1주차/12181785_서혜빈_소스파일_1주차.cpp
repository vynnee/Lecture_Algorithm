#include<stdio.h>

int main() {
	int snum[10];
	int i;
	int max = 0;
	int min = 0;
	int temp = 0;

	printf("숫자를 입력하세요. : ");
	
	for (i = 0; i < 10; i++) {
		scanf_s("%d", &snum[i]);
	} // 숫자 입력

	printf("\n");

	for (i = 0; i < 10; i++) {
		if (max < snum[i])
			max = snum[i];
	} // 최대값 구하기

	for (i = 0; i < 10; i++) {
		if (min > snum[i])
			min = snum[i];
	} // 최소값 구하기

	printf("최소값, 최대값 : %d, %d\n", min, max);


	for (i = 0; i < 10; i++) {
		for (int j = 0; j < (10 - i); j++) {
			if (snum[j] < snum[j + 1]) {
				temp = snum[j];
				snum[j] = snum[j + 1];
				snum[j + 1] = temp;
			}
		}
	} // 역순 정렬

	printf("역순 정렬 : ");

	for (i = 0; i < 10; i++) {
		printf("%d ", snum[i]);
	}

	printf("\n");

	for (i = 9; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (snum[j] > snum[j + 1]) {
				temp = snum[j];
				snum[j] = snum[j + 1];
				snum[j + 1] = temp;
			}
		}
	} // 정순 정렬

	printf("정순 정렬 : ");

	for (i = 0; i < 10; i++) {
		printf("%d ", snum[i]);
	}

	printf("\n");

	printf("정보통신공학과 12181785 서혜빈\n");
}