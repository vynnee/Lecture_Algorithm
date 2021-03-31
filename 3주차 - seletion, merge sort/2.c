#include<stdio.h>

void merge(int *data, int start, int mid, int end);
void merge_sort(int *data, int start, int end);

int sorted[11]; // temp와 같은 역할

int main() {
	int data[10] = { 6, 2, 8, 1, 3, 9, 4, 5, 10, 7 };

	merge_sort(data, 0, 9);

	for (int i = 0; i < 10; i++) {
		printf("%d ", data[i]);
	}

	return 0;
}

void merge(int *data, int start, int mid, int end) {
	int i = start;
	int j = mid + 1;
	int k = start;

	while (i <= mid && j <= end) {
		if (data[i] <= data[j]) { // data[i]가 data[j]보다 작으면
			sorted[k] = data[i]; // data[i]를 sorted[k]에 할당
			i++;
		}
		else { // data[i] > data[j]
			sorted[k] = data[k];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (int t = j; t <= end; t++) {
			sorted[k] = data[t];
			k++;
		}
	}
	else {
		for (int t = i; t <= mid; t++) {
			sorted[k] = data[t];
			k++;
		}
	}
	
	// 정렬된 배열 삽입
	for (int t = start; t <= end; t++) {
		data[t] = sorted[t];
	}
}

void merge_sort(int *data, int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		merge_sort(data, start, mid); // 왼쪽 정렬
		merge_sort(data, mid + 1, end); // 오른쪽 정렬
		merge(data, start, mid, end);
	}
}