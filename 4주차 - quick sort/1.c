#include<stdio.h>

void swap(int arr[], int a, int b) { // a, b swap 함수 구현
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void QuickSort(int arr[], int l, int r) {
	int i, j, mid, pivot;

	mid = (l + r) / 2; // pivot 중간값

	if (arr[l] > arr[mid]) // left가 중간값보다 크면
		swap(arr, l, mid); // left와 중간값 교체
	if (arr[l] > arr[r]) // left가 right보다 크면
		swap(arr, l, r); // left와 right 교체
	if (arr[mid] > arr[r]) // 중간값이 right보다 크면
		swap(arr, mid, r); // 중간값과 right 교체

	if (r - l + 1 > 3) { // 중간값 quick sort는 
						 // 우선적으로 3게의 값들에 대해 정렬을 수행
						 // 만약 정렬 대상이 3개 이하라면 위에서 이미 정렬이 끝남
						 // 따라서 데이터의 개수가 3개 초과일 때만 추가적으로 정렬 수행
		pivot = arr[mid];
		swap(arr, mid, r - 1);
		i = l;
		j = r - 1;

		while (1) { // 정렬 확인하고, left가 right보다 크면 swap
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

	printf("12181785 서혜빈\n");
}