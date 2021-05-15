#include<stdio.h>

int cheese[9][9] = {
	{0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 1, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0} };

int cheeseWithTrap[9][9] = {
	{0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0,2, 0},
	{1, 0, 2, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 1, 2, 0, 0, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 2, 1, 2, 0},
	{0, 1, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0} };

int cheese_find() {
	int max = 0;
	for (int i = 8; i > -1; i--) { // 8��° ����� ����
		for (int j = 0; j < 9; j++) { // 0��° ������ ����
			if (i == 8 && j == 0) // ���������̸�
				continue; // skip

			// �𼭸� ó��
			else if (i == 8) // i �� 8 �� ���� �Ʒ��� �����Ƿ� ������ ������
				cheese[i][j] += cheese[i][j - 1];
			else if (j == 0) // j �� 0 �� ���� j-1�� �����Ƿ�, �Ʒ��� ������
				cheese[i][j] += cheese[i + 1][j];

			else { // ���ʰ� �Ʒ��� �߿��� ū ���� �����ֱ�
				if (cheese[i][j - 1] > cheese[i + 1][j])
					cheese[i][j] += cheese[i][j - 1];
				else
					cheese[i][j] += cheese[i + 1][j];
			}
		}
	}
	return max = cheese[0][8];
}

int trap_find() {
	int max = 0;
	for (int i = 8; i > -1; i--) {
		for (int j = 0; j < 9; j++) {
			if (cheeseWithTrap[i][j] == 2)  // �㵣�̸�
				cheeseWithTrap[i][j] = -1; // -1 �־��ֱ�
			// -1�� �־������ν� ū ���� ��� �����ٶ�, ���õ��� �ʾ� trap�� �ȴ�����

			else {
				if (i == 8 && j == 0)
					continue;
				else if (i == 8)
					cheeseWithTrap[i][j] += cheeseWithTrap[i][j - 1];
				else if (j == 0)
					cheeseWithTrap[i][j] += cheeseWithTrap[i + 1][j];
				else {
					if (cheeseWithTrap[i][j - 1] > cheeseWithTrap[i + 1][j])
						cheeseWithTrap[i][j] += cheeseWithTrap[i][j - 1];
					else
						cheeseWithTrap[i][j] += cheeseWithTrap[i + 1][j];
				}
			}

		}
	}
	return max = cheeseWithTrap[0][8];
}

int main()
{
	int max = 0;
	 max = cheese_find();
	printf("ù ��° ����\n");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", cheese[i][j]);
		}
		printf("\n");
	}
	printf("ġ�� �ִ� ���� : %d\n", max);
	
	printf("\n");

	max = trap_find();
	printf("�� ��° ����\n");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", cheeseWithTrap[i][j]);
		}
		printf("\n");
	}
	printf("ġ�� �ִ� ���� : %d\n", max);

	printf("12181785 ������\n");
	return 0;
}