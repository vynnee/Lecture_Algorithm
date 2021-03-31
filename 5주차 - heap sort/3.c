#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#pragma comment (linker,"/STACK:22496080")

#define N 100000


void swap(int arr[], int a, int b) { // a, b swap 함수 구현
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void heapify(int arr[], int n, int mid) {
	int parent_node = mid;
	int left_node = parent_node * 2;
	int right_node = parent_node * 2 + 1;
	int smallest_node = parent_node;
	int temp;

	if (left_node < n && arr[left_node] < arr[smallest_node]) {
		// left_node에 값이 있는지 확인하고, 비교
		smallest_node = left_node;
	}

	if (right_node < n && arr[right_node] < arr[smallest_node]) {
		// right_node에 값이 있는지 확인하고, 비교
		smallest_node = right_node;
	}

	if (parent_node != smallest_node) {
		swap(arr, smallest_node, parent_node);
		heapify(arr, n, smallest_node);
	}
}

void MinHeapSort(int arr[], int n) {
	int mid = n / 2 - 1; // 중간 node에서 시작(0부터 시작하는 index)

	for (mid; mid >= 0; mid--) { // root node까지 loop
		heapify(arr, n, mid);
	}
}

void HeapSort(int arr[], int n) {
	MinHeapSort(arr, n);

	// root node를 마지막 node와 swap
	// heap의 크기가 1이 될 때까지 loop
	while (n > 1) {
		swap(arr, 0, n - 1);

		n--;
		heapify(arr, n, 0);
	}
}

void checkSort(int arr[], int n) // 정렬이 잘 됐는지 확인
{
	int i, sorted;
	sorted = 1;
	for (i = 0; i < n - 1; i++) {
		if (arr[i] < arr[i + 1]) {
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

int main() {
	int i, j;
	clock_t start, end;
	float res;

	// 동적할당
	int* arr = (int*)malloc(sizeof(int) * N);

	for (j = 0; j < N; j++) {
		arr[j] = malloc(sizeof(int) * N);
	}

	// random 수 생성
	srand(time(NULL));
	for (i = 0; i < N; i++) {
		arr[i] = rand() % 10;
	}

	start = clock();
	HeapSort(arr, N);
	end = clock();
	res = (float)(end - start);

	printf("Min Heap sort 소요시간  : %.3f ms\n", res);
	checkSort(arr, N);
	printf("\n");

	printf("12181785 서혜빈\n");

	// free memory
	for (int j = 0; j < N; j++) {
		free(arr[j]);
	}
	free(arr);
}
