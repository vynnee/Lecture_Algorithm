#include<iostream>
using namespace std;
/**
   * @data  ���� �迭
   * @size  data�� �������� ����
   * @p  ������ �ִ� �ڸ���
   * @k  ���(10������ ����Ѵٸ� 10)
**/

void print(int* data, int n)
{
    for (int i = 0; i < 8; i++) {
        printf("%d ", data[i]);
    }
}

void rxSort(int* data, int size, int p, int k) {
    int* counts, // Ư�� �ڸ����� ���ڵ��� ī��Ʈ
        * temp; // ���ĵ� �迭�� ���� �ӽ� ���
    int index, pval, i, j, n;
    // �޸� �Ҵ�
    if ((counts = (int*)malloc(k * sizeof(int))) == NULL)
        return;
    if ((temp = (int*)malloc(size * sizeof(int))) == NULL)
        return;
    for (n = 0; n < p; n++) { // 1�� �ڸ�, 10���ڸ�, 100�� �ڸ� ������ ����
        for (i = 0; i < k; i++)
            counts[i] = 0; // �ʱ�ȭ
           // ��ġ�� ���.
          // n:0 => 1,  1 => 10, 2 => 100
        pval = (int)pow((double)k, (double)n);
        // �� ������ �߻�Ƚ���� ����.
        for (j = 0; j < size; j++) {
            // 253�̶�� ���ڶ��
            // n:0 => 3,  1 => 5, 2 => 2
            index = (int)(data[j] / pval) % k;
            counts[index] = counts[index] + 1;
        }
        // ī��Ʈ �������� ���Ѵ�. ��������� ���ؼ�.
        for (i = 1; i < k; i++) {
            counts[i] = counts[i] + counts[i - 1];
        }
        // ī��Ʈ�� ����� �� �׸��� ��ġ�� �����Ѵ�.
        // ������� ���
        for (j = size - 1; j >= 0; j--) { // �ڿ������� ����
            index = (int)(data[j] / pval) % k;
            temp[counts[index] - 1] = data[j];
            counts[index] = counts[index] - 1; // �ش� ���� ī��Ʈ�� 1 ����
        }
        // �ӽ� ������ ����
        memcpy(data, temp, size * sizeof(int));
    }

    print(data, 8);
}


int main() {
    int arr[8] = { 170, 45, 75, 90, 2, 24, 802, 66 };

    printf("���� �� : ");

    print(arr, 8);

    printf("\n");

    printf("���� �� : ");

    rxSort(arr, 8, 3, 10);

    printf("\n");
    printf("12181785 ������\n");
}