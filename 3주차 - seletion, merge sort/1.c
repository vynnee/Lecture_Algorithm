#include<stdio.h>

int main() {
	int data[10] = { 6, 2, 8, 1, 3, 9, 4, 5, 10, 7 };
	// 숫자 할당
	int temp;

	printf("Before : ");

	for (int i = 0; i < 10; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");

	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (data[i] > data[j]) { // data[i] 보다 data[j]가 작으면
				temp = data[i];
				data[i] = data[j];
				data[j] = temp; // data[i]와 data[j] 자리 교체
			}
		}
	}

	printf("After : ");

	for (int i = 0; i < 10; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");

	printf("12181785 서혜빈\n");
}