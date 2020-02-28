#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
int main()
{
	int n = 0;
	int i = 0;
	int count = 0;
	scanf("%d", &n);
	if (n <= 2000 || n>2100)
	{
		n = 0;
		count++;
		printf("Invalid year!");
	}
	for (i = 2001; i <= n; i++)
	{
		if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
		{
			printf("%d\n", i);
			count++;
		}
	}
	if (count == 0)
	{
		printf("None");
	}
	system("pause");
	return 0;
}