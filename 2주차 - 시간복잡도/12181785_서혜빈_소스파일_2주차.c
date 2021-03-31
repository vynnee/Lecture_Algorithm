#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int fibonacci(int input);

void main() {
	int input;
	scanf_s("%d", &input);

	int** a = malloc(sizeof(int*) * input);
	int** b = malloc(sizeof(int*) * input);
	int** c = malloc(sizeof(int*) * input);
	int** result = malloc(sizeof(int*) * input);

	// init col
	for (int j = 0; j < input; j++) {
		a[j] = malloc(sizeof(int) * input);
		b[j] = malloc(sizeof(int) * input);
		c[j] = malloc(sizeof(int) * input);
		result[j] = malloc(sizeof(int) * input);

	}

	for (int i = 0; i < input; i++) {
		for (int j = 0; j < input; j++) {
			a[i][j] = 0;
			b[i][j] = 0;
			c[i][j] = 0;
			result[i][j] = 0;
		}
	}

	clock_t start, end;
	float res;

	start = clock();

	// O(n^3)
	int sum;
	for (int i = 0; i < input; i++) {
		for (int j = 0; j < input; j++) {
			sum = 0;
			for (int k = 0; k < input; k++) {
				sum += a[i][k] + b[k][j];
			}
			result[i][j] = sum;
		}
	}

	for (int i = 0; i < input; i++) {
		for (int j = 0; j < input; j++) {
			sum = 0;
			for (int k = 0; k < input; k++) {
				sum += result[i][k] * c[k][j];
			}
			result[i][j] = sum;
		}
	}


	end = clock();
	res = (float)(end - start);

	printf("O(n^3) : %.3f ms\n", res);


	start = clock();

	// O(2^n)
	int num = fibonacci(input);

	end = clock();
	res = (float)(end - start);

	printf("O(2^n) : %.3f ms\n", res);

	// free memory
	for (int j = 0; j < input; j++) {
		free(a[j]);
		free(b[j]);
		free(c[j]);
	}
	free(a);
	free(b);
	free(c);

	printf("12181785 ¼­Çýºó\n");
}

int fibonacci(int input) {
	if (input == 0 || input == 1)
		return 1;
	return fibonacci(input - 1) + fibonacci(input - 2);
}