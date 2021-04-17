#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#pragma comment (linker,"/STACK:22496080")

#define N 1000000

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

void main() {

    int i;
    clock_t start, end;
    float res;

    // 동적할당
    int* arr = (int*)malloc(sizeof(int) * N);

    for (int j = 0; j < N; j++) {
        arr[j] = malloc(sizeof(int) * N);
    }

    // random 수 생성
    srand(time(NULL));
    for (i = 0; i < N; i++) {
        arr[i] = rand() % 10;
    }

    start = clock();
    // 셸 정렬 수행
    shell_sort(arr, N);
    end = clock();
    res = (float)(end - start);

    printf("Shell sort 소요시간  : %.3f ms\n", res);
    checkSort(arr, N);
    printf("\n");

    printf("12181785 서혜빈\n");

    // free memory
    for (int j = 0; j < N; j++) {
        free(arr[j]);
    }
    free(arr);
}
