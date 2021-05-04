#include<stdio.h>
#include<string.h>

int skip[27];
// 27�� ���ĺ��� ��

int index(char a) {
	if (a == 32)
		return 0;
	// a �� space ��, index�� 0
	else
		return (a - 64);
	// �ƽ�Ű�ڵ� A ��  65
	// ���� A - 64 = 1 �̹Ƿ� index�� 1
}

void InitSkip(char* p) {
	int i, M = strlen(p);

	for (i = 0; i < 27; i++)
		skip[i] = M;
	// skip ���� ��� M ���� �ʱ�ȭ

	for (i = 0; i < M; i++)
		skip[index(p[i])] = M - i - 1;
	// index �Լ��� ���� �ƽ�Ű ������ ��ȯ�ϰ�, skip index�� �����ش�.
}

int MisChar(char p[], char t[]) {
	int M = strlen(p);
	int N = strlen(t);
	int i, j, k;

	InitSkip(p);
	for (i = M - 1, j = M - 1; j >= 0; i--, j--) {
		// ���̾� ���� �˰����� �ڿ������� �����ϹǷ� -1�� --
		// �ڿ������� �˻��ϰ� �ε����� �����ϴ� �����̹Ƿ� 0���� �̻��϶��� ����
		while (t[i] != p[j]) { // text�� pattern�� �ٸ� ����
			k = skip[index(t[i])]; // Ʋ�� index�� ���° index ���� ����
			printf("����ġ k = %d, M-j = %d, ", k, M - j);

			if (M - j > k) {
				i = i + M - j; // �̵��Ÿ� �� �� ��
			}
			else if (M - j <= k) {
				i = i + k;
			}

			if (i >= N) {
				return N;
			}

			j = M - 1;
			printf("i = %d, j = %d\n", i, j);
		}
		printf("��ġ %d, %d\n", i, j);
	}
	return i + 1;
}

int main() {
	char t[100] = "VISION QUESTION ONION CAPTION GRADUATION EDUCATION";
	char p[100] = "ATION";

	int M, N;
	int pos = 0;
	int pre = 0;
	int i = 0;

	M = strlen(p);
	N = strlen(t);

	for(;;) {
		pos = MisChar(p, t+pre);
		pos = pos + pre;
		i = pos + M;

		if (i <= N)
			printf("������ �߻��� ��ġ : %d\n", pos);
		else
			break;

		pre = i;
	}
	printf("��Ʈ�� Ž�� ����.\n");
	printf("12181785 ������\n");
}