#include<stdio.h>

void swap(int arr[], int a, int b) { // a, b swap �Լ� ����
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void QuickSort(int arr[], int l, int r) {
	int i, j, mid, pivot;

	mid = (l + r) / 2; // pivot �߰���

	if (arr[l] > arr[mid]) // left�� �߰������� ũ��
		swap(arr, l, mid); // left�� �߰��� ��ü
	if (arr[l] > arr[r]) // left�� right���� ũ��
		swap(arr, l, r); // left�� right ��ü
	if (arr[mid] > arr[r]) // �߰����� right���� ũ��
		swap(arr, mid, r); // �߰����� right ��ü

	if (r - l + 1 > 3) { // �߰��� quick sort�� 
						 // �켱������ 3���� ���鿡 ���� ������ ����
						 // ���� ���� ����� 3�� ���϶�� ������ �̹� ������ ����
						 // ���� �������� ������ 3�� �ʰ��� ���� �߰������� ���� ����
		pivot = arr[mid];
		swap(arr, mid, r - 1);
		i = l;
		j = r - 1;

		while (1) { // ���� Ȯ���ϰ�, left�� right���� ũ�� swap
			while (arr[++i] < pivot && i < r);
			while (arr[--j] > pivot && l < j);
			if (i >= j) break;
			swap(arr, i, j);
		}

		swap(arr, i, r - 1);
		QuickSort(arr, l, i - 1);
		QuickSort(arr, i + 1, r);

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

	QuickSort(arr, 0, n - 1);

	printf("After : ");

	for (int i = 0; i < 10; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	printf("12181785 ������\n");
}