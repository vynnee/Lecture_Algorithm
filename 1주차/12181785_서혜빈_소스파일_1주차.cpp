#include<stdio.h>

int main() {
	int snum[10];
	int i;
	int max = 0;
	int min = 0;
	int temp = 0;

	printf("���ڸ� �Է��ϼ���. : ");
	
	for (i = 0; i < 10; i++) {
		scanf_s("%d", &snum[i]);
	} // ���� �Է�

	printf("\n");

	for (i = 0; i < 10; i++) {
		if (max < snum[i])
			max = snum[i];
	} // �ִ밪 ���ϱ�

	for (i = 0; i < 10; i++) {
		if (min > snum[i])
			min = snum[i];
	} // �ּҰ� ���ϱ�

	printf("�ּҰ�, �ִ밪 : %d, %d\n", min, max);


	for (i = 0; i < 10; i++) {
		for (int j = 0; j < (10 - i); j++) {
			if (snum[j] < snum[j + 1]) {
				temp = snum[j];
				snum[j] = snum[j + 1];
				snum[j + 1] = temp;
			}
		}
	} // ���� ����

	printf("���� ���� : ");

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
	} // ���� ����

	printf("���� ���� : ");

	for (i = 0; i < 10; i++) {
		printf("%d ", snum[i]);
	}

	printf("\n");

	printf("������Ű��а� 12181785 ������\n");
}