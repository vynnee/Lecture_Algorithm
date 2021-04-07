#include<iostream>
using namespace std;
/**
   * @data  정수 배열
   * @size  data의 정수들의 개수
   * @p  숫자의 최대 자리수
   * @k  기수(10진법을 사용한다면 10)
**/

void print(int* data, int n)
{
    for (int i = 0; i < 8; i++) {
        printf("%d ", data[i]);
    }
}

void rxSort(int* data, int size, int p, int k) {
    int* counts, // 특정 자리에서 숫자들의 카운트
        * temp; // 정렬된 배열을 담을 임시 장소
    int index, pval, i, j, n;
    // 메모리 할당
    if ((counts = (int*)malloc(k * sizeof(int))) == NULL)
        return;
    if ((temp = (int*)malloc(size * sizeof(int))) == NULL)
        return;
    for (n = 0; n < p; n++) { // 1의 자리, 10의자리, 100의 자리 순으로 진행
        for (i = 0; i < k; i++)
            counts[i] = 0; // 초기화
           // 위치값 계산.
          // n:0 => 1,  1 => 10, 2 => 100
        pval = (int)pow((double)k, (double)n);
        // 각 숫자의 발생횟수를 센다.
        for (j = 0; j < size; j++) {
            // 253이라는 숫자라면
            // n:0 => 3,  1 => 5, 2 => 2
            index = (int)(data[j] / pval) % k;
            counts[index] = counts[index] + 1;
        }
        // 카운트 누적합을 구한다. 계수정렬을 위해서.
        for (i = 1; i < k; i++) {
            counts[i] = counts[i] + counts[i - 1];
        }
        // 카운트를 사용해 각 항목의 위치를 결정한다.
        // 계수정렬 방식
        for (j = size - 1; j >= 0; j--) { // 뒤에서부터 시작
            index = (int)(data[j] / pval) % k;
            temp[counts[index] - 1] = data[j];
            counts[index] = counts[index] - 1; // 해당 숫자 카운트를 1 감소
        }
        // 임시 데이터 복사
        memcpy(data, temp, size * sizeof(int));
    }

    print(data, 8);
}


int main() {
    int arr[8] = { 170, 45, 75, 90, 2, 24, 802, 66 };

    printf("정렬 전 : ");

    print(arr, 8);

    printf("\n");

    printf("정렬 후 : ");

    rxSort(arr, 8, 3, 10);

    printf("\n");
    printf("12181785 서혜빈\n");
}