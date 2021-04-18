#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#pragma comment (linker,"/STACK:22496080")

#define N 10000000

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

// gap만큼 떨어진 요소들을 삽입 정렬
// 정렬의 범위는 first에서 last까지
void inc_insertion_sort(int arr[], int first, int last, int gap) {
    int i, j, key;

    for (i = first + gap; i <= last; i = i + gap) {
        key = arr[i]; // 현재 삽입될 숫자인 i번째 정수를 key 변수로 복사

        // 현재 정렬된 배열은 i-gap까지이므로 i-gap번째부터 역순으로 조사한다.
        // j 값은 first 이상이어야 하고
        // key 값보다 정렬된 배열에 있는 값이 크면 j번째를 j+gap번째로 이동
        for (j = i - gap; j >= first && arr[j] > key; j = j - gap) {
            arr[j + gap] = arr[j]; // 레코드를 gap만큼 오른쪽으로 이동
        }

        arr[j + gap] = key;
    }
}

// 셸 정렬
void shell_sort(int arr[], int n) {
    int i, gap;

    for (gap = n / 2; gap > 0; gap = gap / 2) {
        if ((gap % 2) == 0) {
            gap++; // gap을 홀수로 만든다.
        }

        // 부분 리스트의 개수는 gap과 같다.
        for (i = 0; i < gap; i++) {
            // 부분 리스트에 대한 삽입 정렬 수행
            inc_insertion_sort(arr, i, n - 1, gap);
        }
    }
}

void checkSort(int arr[], int n) // 정렬이 잘 됐는지 확인
{
    int i, sorted;
    sorted = 1;
    for (i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
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
    int i;
    clock_t start, end;
    float res;

    // 동적할당
    int* arr1 = (int*)malloc(sizeof(int) * N);
    int* arr2 = (int*)malloc(sizeof(int) * N);

    for (int j = 0; j < N; j++) {
        arr1[j] = malloc(sizeof(int) * N);
        arr2[j] = malloc(sizeof(int) * N);
    }

    // random 수 생성
    srand(time(NULL));
    for (i = 0; i < N; i++) {
        arr1[i] = rand() % N;
        arr2[i] = arr1[i];
    }

    start = clock();
    // 셸 정렬 수행
    shell_sort(arr1, N);
    end = clock();
    res = (float)(end - start);

    printf("Shell sort 소요시간  : %.3f ms\n", res);
    checkSort(arr1, N);
    printf("\n");

    start = clock();
    QuickSort(arr2, 0, N - 1);
    end = clock();
    res = (float)(end - start);

    printf("Quick sort 소요시간  : %.3f ms\n", res);
    checkSort(arr2, N);
    printf("\n");

    printf("12181785 서혜빈\n");

    // free memory
    for (int j = 0; j < N; j++) {
        free(arr1[j]);
        free(arr2[j]);
    }
    free(arr1);
    free(arr2);
}