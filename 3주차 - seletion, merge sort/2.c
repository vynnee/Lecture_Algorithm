#include<stdio.h>

void merge(int *data, int start, int mid, int end);
void merge_sort(int *data, int start, int end);

int sorted[11]; // temp�� ���� ����

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
		if (data[i] <= data[j]) { // data[i]�� data[j]���� ������
			sorted[k] = data[i]; // data[i]�� sorted[k]�� �Ҵ�
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
	
	// ���ĵ� �迭 ����
	for (int t = start; t <= end; t++) {
		data[t] = sorted[t];
	}
}

void merge_sort(int *data, int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		merge_sort(data, start, mid); // ���� ����
		merge_sort(data, mid + 1, end); // ������ ����
		merge(data, start, mid, end);
	}
}