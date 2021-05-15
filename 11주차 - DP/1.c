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
	for (int i = 8; i > -1; i--) { // 8번째 행부터 시작
		for (int j = 0; j < 9; j++) { // 0번째 열부터 시작
			if (i == 8 && j == 0) // 시작지점이면
				continue; // skip

			// 모서리 처리
			else if (i == 8) // i 가 8 일 때는 아래가 없으므로 왼쪽을 더해줌
				cheese[i][j] += cheese[i][j - 1];
			else if (j == 0) // j 가 0 일 때는 j-1이 없으므로, 아래를 더해줌
				cheese[i][j] += cheese[i + 1][j];

			else { // 왼쪽과 아래쪽 중에서 큰 값을 더해주기
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
			if (cheeseWithTrap[i][j] == 2)  // 쥐덫이면
				cheeseWithTrap[i][j] = -1; // -1 넣어주기
			// -1을 넣어줌으로써 큰 값을 골라 더해줄때, 선택되지 않아 trap은 안더해짐

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
	printf("첫 번째 문제\n");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", cheese[i][j]);
		}
		printf("\n");
	}
	printf("치즈 최대 개수 : %d\n", max);
	
	printf("\n");

	max = trap_find();
	printf("두 번째 문제\n");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", cheeseWithTrap[i][j]);
		}
		printf("\n");
	}
	printf("치즈 최대 개수 : %d\n", max);

	printf("12181785 서혜빈\n");
	return 0;
}