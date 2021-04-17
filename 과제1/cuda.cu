#include <iostream>
using namespace std;

#include <cuda_runtime.h>       
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define THREADS pow(2,6)
#define BLOCKS pow(2,21)
#define NUM_VALS THREADS*BLOCKS

void print_elapsed(clock_t start, clock_t stop)
{
    double elapsed = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.3fs\n", elapsed);
}

float random_float()
{
    return (float)rand() / (float)RAND_MAX;
}

void array_print(float* arr, int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        printf("%1.3f ", arr[i]);
    }
    printf("\n");
}

void array_fill(float* arr, float* arr2, int* arr3, int length)
{
    srand(time(NULL));
    int i;
    for (i = 0; i < length; ++i) {
        arr[i] = random_float();
        arr2[i] = arr[i];
        arr3[i] = int(arr[i]);
    }
}

void array_fill(int* arr, int length)
{
    srand(time(NULL));
    int i;
    for (i = 0; i < length; ++i) {
        arr[i] = random_float();
    }
}


__global__ void bitonic_sort_step(float* dev_values, int j, int k)
{
    unsigned int i, ixj; /* Sorting partners: i and ixj */
    i = threadIdx.x + blockDim.x * blockIdx.x;//blockIdx.x로 복사본 구분

    ixj = i ^ j;

    /* The threads with the lowest ids sort the array. */
    if ((ixj) > i) {
        if ((i & k) == 0) {
            /* Sort ascending */
            if (dev_values[i] > dev_values[ixj]) {
                /* exchange(i,ixj); */
                float temp = dev_values[i];
                dev_values[i] = dev_values[ixj];
                dev_values[ixj] = temp;
            }
        }
        if ((i & k) != 0) {
            /* Sort descending */
            if (dev_values[i] < dev_values[ixj]) {
                /* exchange(i,ixj); */
                float temp = dev_values[i];
                dev_values[i] = dev_values[ixj];
                dev_values[ixj] = temp;
            }
        }
    }
}

void bitonic_sort(float* values)
{
    float* dev_values;
    size_t size = NUM_VALS * sizeof(float);

    cudaMalloc((void**)&dev_values, size);
    cudaMemcpy(dev_values, values, size, cudaMemcpyHostToDevice);

    // <<<>>>>의 첫번째 인자에 3차원까지 지정가능 이것은 2차원인데 1이므로
    // BLOCKS*1 =BLOCKS수만큼들어감
    dim3 blocks(BLOCKS, 1);    /* Number of blocks   */
    dim3 threads(THREADS, 1);  /* Number of threads  */

    int j, k;
    /* Major step */
    for (k = 2; k <= NUM_VALS; k <<= 1) {
        /* Minor step */
        for (j = k >> 1; j > 0; j = j >> 1) {
            bitonic_sort_step << <blocks, threads >> > (dev_values, j, k);
            //blocks 만큼 복사본 생성(할당) 되고, 각각 block에 Threads개의 스레드가 실행함
            //총 작업수는 그럼 몇이게? 쓰레드*블럭수 만큼
        }
    }
    cudaMemcpy(values, dev_values, size, cudaMemcpyDeviceToHost);
    cudaFree(dev_values);
}


//cpu
void compAndSwap(int a[], int i, int j, int dir)
{
    if (dir == (a[i] > a[j]))
        swap(a[i], a[j]);
}

void bitonicMerge(int a[], int low, int cnt, int dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++)
            compAndSwap(a, i, i + k, dir);
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low + k, k, dir);
    }
}
void bitonicSort(int a[], int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        bitonicSort(a, low, k, 1);
        bitonicSort(a, low + k, k, 0);
        bitonicMerge(a, low, cnt, dir);
    }
}

#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#pragma comment (linker,"/STACK:22496080")

void swap(int* arr, int a, int b) { // a, b swap 함수 구현
    float temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void QuickSort(int* arr, int l, int r) {
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
void inc_insertion_sort(float* arr, int first, int last, int gap) {
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
void shell_sort(float* arr, int n) {
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


int main(void) {
    clock_t start, stop;
    float* values = (float*)malloc(NUM_VALS * sizeof(float));
    float* values2 = (float*)malloc(NUM_VALS * sizeof(float));
    int* values3 = (int*)malloc(NUM_VALS * sizeof(int));
    array_fill(values, values2, values3, NUM_VALS);

    start = clock();
    bitonic_sort(values);
    stop = clock();
    cout << "cuda ";
    print_elapsed(start, stop);

    start = clock();
    shell_sort(values2, NUM_VALS);
    stop = clock();
    cout << "shell sort ";
    print_elapsed(start, stop);


    start = clock();
    QuickSort(values3, 0, NUM_VALS-1);
    stop = clock();
    cout << "quick sort ";
    print_elapsed(start, stop);
}