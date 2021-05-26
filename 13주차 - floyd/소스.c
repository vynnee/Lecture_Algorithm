#include<stdio.h>

#define Far_Distance 2000
#define n 6

// W[i][j] : i에서 j까지의 가중치
// Far_Distance는 바로 갈 수 없는 경우
int W[n][n] = {
	{ 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, Far_Distance,1, 5 },
	{ 0, 9, 0, 3, 2, Far_Distance },
	{ 0, Far_Distance, Far_Distance, 0, 4, Far_Distance },
	{ 0, Far_Distance, Far_Distance, 2, 0, 3 },
	{ 0, 3, Far_Distance, Far_Distance, Far_Distance, 0 }
};

int D[n][n]; // i에서 j까지의 최단 거리 저장
int P[n][n]; // i에서 j까지 가는 데 거치는 최고 차수 정점을 저장

void floyd2() {
	int i, j, k;

	// 배열 초기화
	for (i = 1; i < n; i++) {
		for (j = 1; j < n; j++) {
			P[i][j] = 0;
			D[i][j] = W[i][j];
		}
	}

	for (k = 1; k < n; k++) {
		for (i = 1; i < n; i++) {
			for (j = 1; j <= n; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
				// k를 거칠 시 D[i][j]가 더 짧아지는 경우
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}

void path(int q, int r) {
	if (P[q][r] != 0) {
		path(q, P[q][r]); // 왼쪽
		printf(" v%d ->", P[q][r]);
		path(P[q][r], r); // 오른쪽
	}
}

int main() {
	floyd2(); // floyd 호출
	int q, r;

	// q, r 입력
	printf("입력 : ");
	scanf_s("%d %d", &q, &r);


	// D[i][j] 출력
	printf("D[i][j] is \n");
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			printf("%d ", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");


	// P[i][j] 출력
	printf("P[i][j] is \n");
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			printf("%d ", P[i][j]);
		}
		printf("\n");
	}
	printf("\n");


	// 최단 경로 출력
	printf("The shortest path(%d, %d) is v%d ->", q, r, q);
	path(q, r); // path 호출
	printf(" v%d\n", r);

	printf("12181785 서혜빈\n");

	return 0;
}