#include<stdio.h>

int main() {
	int data[10] = { 6, 2, 8, 1, 3, 9, 4, 5, 10, 7 };
	// ���� �Ҵ�
	int temp;

	printf("Before : ");

	for (int i = 0; i < 10; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");

	for (int i = 0; i < 9; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (data[i] > data[j]) { // data[i] ���� data[j]�� ������
				temp = data[i];
				data[i] = data[j];
				data[j] = temp; // data[i]�� data[j] �ڸ� ��ü
			}
		}
	}

	printf("After : ");

	for (int i = 0; i < 10; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");

	printf("12181785 ������\n");
}