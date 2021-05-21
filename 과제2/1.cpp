#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

float dist[100][100] = { 0 };

int levenshtein(char source[], char target[]) {
	for (int i = 1; i <= 5; i++)
		dist[i][0] = dist[i-1][0] + 0.7;
	for (int j = 1; j <= 6; j++)
		dist[0][j] = dist[0][j-1] + 0.5;

	for (int j = 1; j <= 6; j++) {
		for (int i = 1; i <= 5; i++) {
			if (source[i - 1] == target[j - 1])
				dist[i][j] = dist[i - 1][j - 1];
			else
				dist[i][j] = min(dist[i - 1][j - 1] + 0.3, 
					min(dist[i][j - 1] + 0.7, dist[i - 1][j] + 0.5));
		}
	}

	for (int j = 0; j <= 6; j++) {
		for (int i = 0; i <= 5; i++) {
			printf("%.1f ", dist[i][j]);
		}
		printf("\n");
	}
	
	return dist[5][6];
}

void main() {
	char source[20] = "GUMBO";
	char target[20] = "GAMBOL";

	int LD = 0;

	LD = levenshtein(source, target);

	printf("LD : %d\n", LD);
}