#include<stdio.h>

void swap(int arr[], int a, int b) { // a, b swap 함수 구현
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void heapify(int arr[], int n, int mid) {
	int parent_node = mid;
	int left_node = parent_node * 2;
	int right_node = parent_node * 2 + 1;
	int largest_node = parent_node;
	int temp;

	if (left_node < n && arr[left_node] > arr[largest_node]) {
		// left_node에 값이 있는지 확인하고, 비교
		largest_node = left_node;
	}

	if (right_node < n && arr[right_node] > arr[largest_node]) {
		// right_node에 값이 있는지 확인하고, 비교
		largest_node = right_node;
	}

	if (parent_node != largest_node) {
		swap(arr, largest_node, parent_node); // swap
		heapify(arr, n, largest_node); // swap 후 다시 heapify
	}
}

void MaxHeapSort(int arr[], int n) {
	int mid = n / 2 - 1; // 중간 node에서 시작(0부터 시작하는 index)

	for (mid; mid >= 0; mid--) { // root node까지 loop
		heapify(arr, n, mid);
	}
}

void HeapSort(int arr[], int n) {
	MaxHeapSort(arr, n);

	// root node를 마지막 node와 swap
	// heap의 크기가 1이 될 때까지 loop
	while (n > 1) {
		swap(arr, 0, n - 1);

		n--;
		heapify(arr, n, 0);
	}
}

int main() {
	int n = 10, i;
	int arr[10] = { 6, 2, 8, 1, 3, 9, 4, 5, 10, 7 };

	printf("Before : ");

	for (int i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	HeapSort(arr, n);

	printf("After : ");

	for (int i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	printf("12181785 서혜빈\n");
}