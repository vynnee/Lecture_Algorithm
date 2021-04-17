#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#pragma comment (linker,"/STACK:22496080")

#define N 10000000

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

int main() {
    int i;
    clock_t start, end;
    float res;

    // �����Ҵ�
    int* arr1 = (int*)malloc(sizeof(int) * N);
    int* arr2 = (int*)malloc(sizeof(int) * N);

    for (int j = 0; j < N; j++) {
        arr1[j] = malloc(sizeof(int) * N);
        arr2[j] = malloc(sizeof(int) * N);
    }

    // random �� ����
    srand(time(NULL));
    for (i = 0; i < N; i++) {
        arr1[i] = rand() % N;
        arr2[i] = arr1[i];
    }

    start = clock();
    // �� ���� ����
    shell_sort(arr1, N);
    end = clock();
    res = (float)(end - start);

    printf("Shell sort �ҿ�ð�  : %.3f ms\n", res);
    checkSort(arr1, N);
    printf("\n");

    start = clock();
    QuickSort(arr2, 0, N - 1);
    end = clock();
    res = (float)(end - start);

    printf("Quick sort �ҿ�ð�  : %.3f ms\n", res);
    checkSort(arr2, N);
    printf("\n");

    printf("12181785 ������\n");

    // free memory
    for (int j = 0; j < N; j++) {
        free(arr1[j]);
        free(arr2[j]);
    }
    free(arr1);
    free(arr2);
}