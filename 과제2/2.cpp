#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

int stack[100];

double dist[100][100];

double levenshtein(string source, string target) {
	dist[0][0] = 0; // ����� �� ó�� 0���� �ʱ�ȭ

	// �ѱ� �Է� ���� ��츦 ���� ���� ��Ʈ�� ����
	vector<string> sourceVec;
	vector<string> targetVec;

	// �Է¹��� source�� target�� �ѱ��̸�
	if ((source[0] & 0x80) && (target[0] & 0x80)) {
		// �� ���� �ɰ��� ���Ϳ� push_back
		for (int i = 0; i < (int)source.size(); i += 2)
			sourceVec.push_back(source.substr(i, 2));
		for (int j = 0; j < (int)target.size(); j += 2)
			targetVec.push_back(target.substr(j, 2));

		for (int i = 1; i <= sourceVec.size(); i++)
			dist[i][0] = dist[i - 1][0] + 0.5; // ��
		for (int j = 1; j <= targetVec.size(); j++)
			dist[0][j] = dist[0][j - 1] + 0.7; // ��
		for (int i = 1; i <= sourceVec.size(); i++) {
			for (int j = 1; j <= targetVec.size(); j++) {
				if (sourceVec[i - 1] == targetVec[j - 1])
					dist[i][j] = dist[i - 1][j - 1];
				else // ��, ��, �밢�� �� �� �ּҰ� �־���
					dist[i][j] = min(dist[i - 1][j - 1] + 0.3,
						min(dist[i][j - 1] + 0.7, dist[i - 1][j] + 0.5));
			}
		}

		// ��� ���
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
				// ���õ� �ּҰ��� �밢�� ���̰�, ���� �������
				printf("��ȯ���� : 0.3, "); // ��ȯ����
				i--;
				j--;
				// �밢�� ������ �̵�
			}
			else if (minimum == dist[i - 1][j]) {
				// ���õ� �ּҰ��� ���� ���� ���
				printf("�������� : 0.5, "); // ��������
				i--;
				// �� ������ �̵�
			}
			else if (minimum == dist[i][j - 1]) {
				// ���õ� �ּҰ��� ���� ���� ���
				printf("���Կ��� : 0.7, "); // ���Կ���
				j--; // ���� ������ �̵�
			}
			else if (minimum == dist[i][j]) {
				// ���õ� �ּҰ��� ���簪�� ���� ���
				i--;
				j--;
				// �׳� �밢�� ������ �̵�
			}

			if (i == 1)
				break;
			// �� �� ������ �� ó�� ������ �̵��� �Ϸ��� ��� break
		}

		return dist[sourceVec.size()][targetVec.size()];
		// ����� �� �� �� return
	}

	// �ѱ��� �ƴϸ�
	else {
		for (int i = 1; i <= source.length(); i++)
			dist[i][0] = dist[i - 1][0] + 0.5; // ��
		for (int j = 1; j <= target.length(); j++)
			dist[0][j] = dist[0][j - 1] + 0.7; // ��
		for (int i = 1; i <= source.length(); i++) {
			for (int j = 1; j <= target.length(); j++) {
				if (source[i - 1] == target[j - 1]) // i-1 ��İ��� j-1 ����� ���� ������
					dist[i][j] = dist[i - 1][j - 1]; // �밢���� �� �־���
				else // ��, ��, �밢�� �� �� �ּҰ� �־���
					dist[i][j] = min(dist[i - 1][j - 1] + 0.3,
						min(dist[i][j - 1] + 0.7, dist[i - 1][j] + 0.5));
			}
		}

		// ��� ���
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
				printf("��ȯ���� : 0.3, ");
				i--;
				j--;
			}
			else if (minimum == dist[i-1][j]) {
				printf("�������� : 0.5, ");
				i--;
			}
			else if (minimum == dist[i][j-1]) {
				printf("���Կ��� : 0.7, ");
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

	printf("12181785 ������\n");
}