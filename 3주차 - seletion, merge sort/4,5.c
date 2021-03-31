#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define N 100000
#define TRUE 1
#define FALSE 0

int sorted[N+1];

void selectionSort(int data[], int n) {
	int temp;

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N + 1; j++) {
			if (data[i] > data[j]) {
				temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
		}
	}
}

void merge(int data[], int start, int mid, int end) {
	int i = start;
	int j = mid + 1;
	int k = start;

	while (i <= mid && j <= end) {
		if (data[i] <= data[j]) {
			sorted[k] = data[i];
			i++;
		}
		else {
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

	for (int t = start; t <= end; t++) {
		data[t] = sorted[t];
	}
}

void merge_sort(int data[], int start, int end) {
	if (start < end) { // 왼쪽보다 오른쪽이 크면
		int mid = (start + end) / 2;
		merge_sort(data, start, mid);
		merge_sort(data, mid + 1, end);
		merge(data, start, mid, end);
	}
}

void checkSort(int a[], int n)
{
	int i, sorted;
	sorted = 1;
	for (i = 0; i < n - 1; i++) {
		if (a[i] > a[i + 1]) {
			sorted = 0;
		}
		if (!sorted) {
			break;
		}
	}
	if (sorted) {
		printf("Sorting complete!");
	}
	else {
		printf("Error during sorting...");
	}
}

void main() {
	clock_t start, end;
	float res;
	int i;

	// 동적할당
	int* data = (int*)malloc(sizeof(int) * N);

	srand(time(NULL));
	for (i = 0; i < N; i++) {
		data[i] = rand() % 10;
	}

	// selection sort
	start = clock();
	selectionSort(data, N);
	end = clock();
	res = (float)(end - start);

	printf("Selection sort 소요시간  : %.3f ms\n", res);
	checkSort(data, N);
	printf("\n");

	// merge sort
	start = clock();
	merge_sort(data, 0, N-1);
	end = clock();
	res = (float)(end - start);

	printf("Merge sort 소요시간  : %.3f ms\n", res);
	checkSort(data, N);
	printf("\n");

	printf("12181785 서혜빈\n");
}