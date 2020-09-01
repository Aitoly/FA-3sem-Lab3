#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include<Windows.h>

int countl(int num)
{
	int count = 0;
	while (num)
	{
		if (num & 1) count++;
		num >>= 1;
	}
	return count;
}

int* comparing(int k, int l)
{
	int max = 1 << k;
	int count = 0, i;
	int* ar = NULL, * ptr = NULL;
	for (i = 0; i < max; i++)
	{
		if (countl(i) == l)
		{
			ptr = (int*)realloc(ar, (++count + 1) * sizeof(int));
			if (!ptr) exit(-1);
			ar = ptr;
			ar[count] = i;
		}
	}
	ar[0] = count;
	return ar;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int* arr;
	int count, k, l;
	printf("¬ведите k, l\n");
	scanf("%d %d", &k, &l);
	printf("\n\n");
	arr = comparing(k, l);
	count = arr[0];
	for (int i = 1; i <= count; i++) printf("%d \n", arr[i]);
	free(arr);
	return 0;
}