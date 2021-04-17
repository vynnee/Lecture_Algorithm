#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#pragma comment (linker,"/STACK:22496080")

#define N 1000000

// gap��ŭ ������ ��ҵ��� ���� ����
// ������ ������ first���� last����
void inc_insertion_sort(int arr[], int first, int last, int gap) {
    int i, j, key;

    for (i = first + gap; i <= last; i = i + gap) {
        key = arr[i]; // ���� ���Ե� ������ i��° ������ key ������ ����

        // ���� ���ĵ� �迭�� i-gap�����̹Ƿ� i-gap��°���� �������� �����Ѵ�.
        // j ���� first �̻��̾�� �ϰ�
        // key ������ ���ĵ� �迭�� �ִ� ���� ũ�� j��°�� j+gap��°�� �̵�
        for (j = i - gap; j >= first && arr[j] > key; j = j - gap) {
            arr[j + gap] = arr[j]; // ���ڵ带 gap��ŭ ���������� �̵�
        }

        arr[j + gap] = key;
    }
}

// �� ����
void shell_sort(int arr[], int n) {
    int i, gap;

    for (gap = n / 2; gap > 0; gap = gap / 2) {
        if ((gap % 2) == 0) {
            gap++; // gap�� Ȧ���� �����.
        }

            // �κ� ����Ʈ�� ������ gap�� ����.
            for (i = 0; i < gap; i++) {
                // �κ� ����Ʈ�� ���� ���� ���� ����
                inc_insertion_sort(arr, i, n - 1, gap);
            }
    }
}

void checkSort(int arr[], int n) // ������ �� �ƴ��� Ȯ��
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

    // �����Ҵ�
    int* arr = (int*)malloc(sizeof(int) * N);

    for (int j = 0; j < N; j++) {
        arr[j] = malloc(sizeof(int) * N);
    }

    // random �� ����
    srand(time(NULL));
    for (i = 0; i < N; i++) {
        arr[i] = rand() % 10;
    }

    start = clock();
    // �� ���� ����
    shell_sort(arr, N);
    end = clock();
    res = (float)(end - start);

    printf("Shell sort �ҿ�ð�  : %.3f ms\n", res);
    checkSort(arr, N);
    printf("\n");

    printf("12181785 ������\n");

    // free memory
    for (int j = 0; j < N; j++) {
        free(arr[j]);
    }
    free(arr);
}
