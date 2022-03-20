#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
int tot(int* parr);

int main()
{
	int arr[6], i;

	printf("숫자를 입력하세요 : ");

	for (i = 0; i < 6; i++)
		scanf_s("%d", &arr[i]);

	printf("%d\n", tot(arr));
}

int tot(int* parr)
{
	int n, i;

	n = 0;
	for (int i = 0; i < 6; i++)
		n = n + *parr++;

	return n;
}