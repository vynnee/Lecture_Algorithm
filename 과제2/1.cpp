#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

int dist[100][100] = { 0 };

int levenshtein(char source[], char target[]) {
	// 행과 열을 1, 2, 3, 4, 5, ... 으로 만들어줌
	for (int i = 1; i <= 5; i++)
		dist[i][0] = dist[i-1][0] + 1;
	for (int j = 1; j <= 6; j++)
		dist[0][j] = dist[0][j-1] + 1;

	for (int j = 1; j <= 6; j++) {
		for (int i = 1; i <= 5; i++) {
			// source의 i-1과 target의 j-1이 같을 경우
			if (source[i - 1] == target[j - 1])
				dist[i][j] = dist[i - 1][j - 1];
				// 대각선 값을 넣어줌
			// 앞, 위, 대각선 비교 후 최소값 넣어줌
			else
				dist[i][j] = min(dist[i - 1][j - 1] + 1, 
					min(dist[i][j - 1] + 1, dist[i - 1][j] + 1));
		}
	}

	// 행렬 출력
	for (int j = 0; j <= 6; j++) {
		for (int i = 0; i <= 5; i++) {
			printf("%d ", dist[i][j]);
		}
		printf("\n");
	}
	
	// 행렬의 마지막 값 return
	return dist[5][6];
}

void main() {
	char source[20] = "GUMBO";
	char target[20] = "GAMBOL";

	int LD = 0;

	LD = levenshtein(source, target);

	printf("LD : %d\n", LD);
	printf("12181785 서혜빈\n");
}