#include <iostream>
using namespace std;

#include <cuda_runtime.h>       
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define THREADS 512 // 2^?
#define BLOCKS 2048 // 2^?
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

void array_fill(float* arr, int length)
{
    srand(time(NULL));
    int i;
    for (i = 0; i < length; ++i) {
        arr[i] = random_float();
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
void bitonicSort(int a[], int low, int cnt, int dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;

        // sort in ascending order since dir here is 1
        bitonicSort(a, low, k, 1);

        // sort in descending order since dir here is 0
        bitonicSort(a, low + k, k, 0);

        // Will merge wole sequence in ascending order
        // since dir=1.
        bitonicMerge(a, low, cnt, dir);
    }
}





int main(void)
{
    clock_t start, stop;

    float* values = (float*)malloc(NUM_VALS * sizeof(float));
    array_fill(values, NUM_VALS);

    start = clock();
    bitonic_sort(values);
    stop = clock();
    cout << "cuda ";
    print_elapsed(start, stop);


    int* values2 = (int*)malloc(NUM_VALS * sizeof(float));
    array_fill(values2, NUM_VALS);

    start = clock();
    bitonicSort(values2, 0, NUM_VALS, 1);
    stop = clock();
    cout << "cpu ";
    print_elapsed(start, stop);
}