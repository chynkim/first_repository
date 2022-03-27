#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{	
	int arr[6], i, j, n, t, sw;
	n = 6;

	printf("숫자를 6개 입력하세요 : ");

	for(i=0; i<n; i++)
		scanf_s("%d", &arr[i]);

	for (i = 0; i < n - 1; i++) {
		sw = 0;
		for (j = 1; j < n ; j++)
			if (arr[j - 1] > arr[j]) {
				t = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = t;
				sw = 1;
			}	
		if (sw == 0)
			break;
	}
	printf("[");
	for (i = 0; i < n; i++) {
		printf("%4d", arr[i]);
		if (i < n)
			printf(", ");
	}
	printf("]");
}