#include<stdio.h>

#define Far_Distance 2000
#define n 6

// W[i][j] : i���� j������ ����ġ
// Far_Distance�� �ٷ� �� �� ���� ���
int W[n][n] = {
	{ 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, Far_Distance,1, 5 },
	{ 0, 9, 0, 3, 2, Far_Distance },
	{ 0, Far_Distance, Far_Distance, 0, 4, Far_Distance },
	{ 0, Far_Distance, Far_Distance, 2, 0, 3 },
	{ 0, 3, Far_Distance, Far_Distance, Far_Distance, 0 }
};

int D[n][n]; // i���� j������ �ִ� �Ÿ� ����
int P[n][n]; // i���� j���� ���� �� ��ġ�� �ְ� ���� ������ ����

void floyd2() {
	int i, j, k;

	// �迭 �ʱ�ȭ
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
				// k�� ��ĥ �� D[i][j]�� �� ª������ ���
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}

void path(int q, int r) {
	if (P[q][r] != 0) {
		path(q, P[q][r]); // ����
		printf(" v%d ->", P[q][r]);
		path(P[q][r], r); // ������
	}
}

int main() {
	floyd2(); // floyd ȣ��
	int q, r;

	// q, r �Է�
	printf("�Է� : ");
	scanf_s("%d %d", &q, &r);


	// D[i][j] ���
	printf("D[i][j] is \n");
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			printf("%d ", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");


	// P[i][j] ���
	printf("P[i][j] is \n");
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < n; j++) {
			printf("%d ", P[i][j]);
		}
		printf("\n");
	}
	printf("\n");


	// �ִ� ��� ���
	printf("The shortest path(%d, %d) is v%d ->", q, r, q);
	path(q, r); // path ȣ��
	printf(" v%d\n", r);

	printf("12181785 ������\n");

	return 0;
}