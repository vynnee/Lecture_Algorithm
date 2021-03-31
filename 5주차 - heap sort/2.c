#include<stdio.h>

void swap(int arr[], int a, int b) { // a, b swap �Լ� ����
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
		// left_node�� ���� �ִ��� Ȯ���ϰ�, ��
		smallest_node = left_node;
	}

	if (right_node < n && arr[right_node] < arr[smallest_node]) {
		// right_node�� ���� �ִ��� Ȯ���ϰ�, ��
		smallest_node = right_node;
	}

	if (parent_node != smallest_node) {
		swap(arr, smallest_node, parent_node); // swap
		heapify(arr, n, smallest_node); // swap �� �ٽ� heapify
	}
}

void MinHeapSort(int arr[], int n) {
	int mid = n / 2 - 1; // �߰� node���� ����(0���� �����ϴ� index)

	for (mid; mid >= 0; mid--) { // root node���� loop
		heapify(arr, n, mid);
	}
}

void HeapSort(int arr[], int n) {
	MinHeapSort(arr, n);

	// root node�� ������ node�� swap
	// heap�� ũ�Ⱑ 1�� �� ������ loop
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

	printf("12181785 ������\n");
}