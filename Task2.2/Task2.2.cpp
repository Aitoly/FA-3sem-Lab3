#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include<Windows.h>

bool funcop(int num, int l)
{
	int cmp = l;

	while (num)
	{
		if (num & 1) cmp--;
		if ((cmp < 0) || ((!(num & 1)) && cmp < l)) return false;
		num >>= 1;
	}

	return !cmp;
}

int* func(int k, int l)
{
	int max = 1 << k;
	int count = 0, i;
	int* ar = NULL, * ptr = NULL;

	for (i = 0; i < max; i++)
	{
		if (funcop(i, l))
		{
			ptr = (int*)realloc(ar, (++count + 1) * sizeof(int));
			if (ptr == NULL) exit(-1);
			else ar = ptr;
			ar[count] = i;
		}
	}
	ar[0] = count;
	return ar;
}

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int* arr;
	int count, k, l;
	printf("¬ведите k, l\n");
	scanf("%d %d", &k, &l);
	printf("\n\n");
	arr = func(k, l);
	count = arr[0];
	for (int i = 1; i <= count; i++) printf("%d \n", arr[i]);
	free(arr);
	return 0;
}
