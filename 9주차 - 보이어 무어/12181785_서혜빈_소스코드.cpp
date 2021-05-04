#include<stdio.h>
#include<string.h>

int skip[27];
// 27은 알파벳의 수

int index(char a) {
	if (a == 32)
		return 0;
	// a 가 space 면, index는 0
	else
		return (a - 64);
	// 아스키코드 A 는  65
	// 따라서 A - 64 = 1 이므로 index는 1
}

void InitSkip(char* p) {
	int i, M = strlen(p);

	for (i = 0; i < 27; i++)
		skip[i] = M;
	// skip 값을 모두 M 으로 초기화

	for (i = 0; i < M; i++)
		skip[index(p[i])] = M - i - 1;
	// index 함수를 통해 아스키 값으로 변환하고, skip index를 맞춰준다.
}

int MisChar(char p[], char t[]) {
	int M = strlen(p);
	int N = strlen(t);
	int i, j, k;

	InitSkip(p);
	for (i = M - 1, j = M - 1; j >= 0; i--, j--) {
		// 보이어 무어 알고리즘은 뒤에서부터 접근하므로 -1과 --
		// 뒤에서부터 검사하고 인덱스를 감소하는 형식이므로 0보다 이상일때만 동작
		while (t[i] != p[j]) { // text와 pattern이 다른 동안
			k = skip[index(t[i])]; // 틀린 index가 몇번째 index 인지 저장
			printf("불일치 k = %d, M-j = %d, ", k, M - j);

			if (M - j > k) {
				i = i + M - j; // 이동거리 중 긴 것
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
		printf("일치 %d, %d\n", i, j);
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
			printf("패턴이 발생한 위치 : %d\n", pos);
		else
			break;

		pre = i;
	}
	printf("스트링 탐색 종료.\n");
	printf("12181785 서혜빈\n");
}