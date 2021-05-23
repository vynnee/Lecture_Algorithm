#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

int stack[100];

double dist[100][100];

double levenshtein(string source, string target) {
	dist[0][0] = 0; // 행렬의 맨 처음 0으로 초기화

	// 한글 입력 받을 경우를 위한 벡터 스트링 선언
	vector<string> sourceVec;
	vector<string> targetVec;

	// 입력받은 source와 target이 한글이면
	if ((source[0] & 0x80) && (target[0] & 0x80)) {
		// 두 개씩 쪼개어 벡터에 push_back
		for (int i = 0; i < (int)source.size(); i += 2)
			sourceVec.push_back(source.substr(i, 2));
		for (int j = 0; j < (int)target.size(); j += 2)
			targetVec.push_back(target.substr(j, 2));

		for (int i = 1; i <= sourceVec.size(); i++)
			dist[i][0] = dist[i - 1][0] + 0.5; // 행
		for (int j = 1; j <= targetVec.size(); j++)
			dist[0][j] = dist[0][j - 1] + 0.7; // 열
		for (int i = 1; i <= sourceVec.size(); i++) {
			for (int j = 1; j <= targetVec.size(); j++) {
				if (sourceVec[i - 1] == targetVec[j - 1])
					dist[i][j] = dist[i - 1][j - 1];
				else // 위, 옆, 대각선 비교 후 최소값 넣어줌
					dist[i][j] = min(dist[i - 1][j - 1] + 0.3,
						min(dist[i][j - 1] + 0.7, dist[i - 1][j] + 0.5));
			}
		}

		// 행렬 출력
		for (int j = 0; j <= targetVec.size(); j++) {
			for (int i = 0; i <= sourceVec.size(); i++) {
				printf("%.1f ", dist[i][j]);
			}
			printf("\n");
		}

		double latest = dist[sourceVec.size()][targetVec.size()];
		double minimum = 0;

		int i = sourceVec.size();
		int j = targetVec.size();

		while (i >= 1) {
			minimum = min(dist[i - 1][j - 1], min(dist[i][j - 1], dist[i - 1][j]));

			if ((minimum == dist[i - 1][j - 1]) && (minimum != dist[i][j])) {
				// 선택된 최소값이 대각선 위이고, 같지 않을경우
				printf("교환연산 : 0.3, "); // 교환연산
				i--;
				j--;
				// 대각선 값으로 이동
			}
			else if (minimum == dist[i - 1][j]) {
				// 선택된 최소값이 위의 값일 경우
				printf("삭제연산 : 0.5, "); // 삭제연산
				i--;
				// 위 값으로 이동
			}
			else if (minimum == dist[i][j - 1]) {
				// 선택된 최소값이 옆의 값일 경우
				printf("삽입연산 : 0.7, "); // 삽입연산
				j--; // 옆의 값으로 이동
			}
			else if (minimum == dist[i][j]) {
				// 선택된 최소값과 현재값이 같을 경우
				i--;
				j--;
				// 그냥 대각선 값으로 이동
			}

			if (i == 1)
				break;
			// 맨 끝 값에서 맨 처음 값으로 이동을 완료한 경우 break
		}

		return dist[sourceVec.size()][targetVec.size()];
		// 행렬의 맨 끝 값 return
	}

	// 한글이 아니면
	else {
		for (int i = 1; i <= source.length(); i++)
			dist[i][0] = dist[i - 1][0] + 0.5; // 행
		for (int j = 1; j <= target.length(); j++)
			dist[0][j] = dist[0][j - 1] + 0.7; // 열
		for (int i = 1; i <= source.length(); i++) {
			for (int j = 1; j <= target.length(); j++) {
				if (source[i - 1] == target[j - 1]) // i-1 행렬값과 j-1 행렬의 값이 같으면
					dist[i][j] = dist[i - 1][j - 1]; // 대각선의 값 넣어줌
				else // 위, 옆, 대각선 비교 후 최소값 넣어줌
					dist[i][j] = min(dist[i - 1][j - 1] + 0.3,
						min(dist[i][j - 1] + 0.7, dist[i - 1][j] + 0.5));
			}
		}

		// 행렬 출력
		for (int j = 0; j <= target.length(); j++) {
			for (int i = 0; i <= source.length(); i++) {
				printf("%.1f ", dist[i][j]);
			}
			printf("\n");
		}

		double latest = dist[source.length()][target.length()];
		double minimum = 0;

		int i = source.length();
		int j = target.length();

		while (i >= 1) {
			minimum = min(dist[i - 1][j - 1], min(dist[i][j - 1], dist[i - 1][j]));

			if ((minimum == dist[i-1][j-1]) && (minimum != dist[i][j])) {
				printf("교환연산 : 0.3, ");
				i--;
				j--;
			}
			else if (minimum == dist[i-1][j]) {
				printf("삭제연산 : 0.5, ");
				i--;
			}
			else if (minimum == dist[i][j-1]) {
				printf("삽입연산 : 0.7, ");
				j--;
			}
			else if (minimum == dist[i][j]) {
				i--;
				j--;
			}
			if (i == 1)
				break;
		}

		return dist[source.length()][target.length()];
	}
}

void main() {
	string source;
	string target;

	double LD = 0;

	cin >> source;
	cin >> target;

	LD = levenshtein(source, target);

	printf("LD : %.1f\n", LD);

	printf("12181785 서혜빈\n");
}