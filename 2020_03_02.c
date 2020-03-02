#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
int main()
{
	int n = 0;
	int x = 0;
	int j = 0;
	int count = 0;
	int sum = 0;
	scanf("%d %d", &n, &x);
	int i = 0;
	for (i = n; i <= x; i++)
	{
		for (j = 2; j < i; j++)
		{
			if (i%j == 0)
			{
				break;
			}
		}
		if (i == j)
		{
			count++;
			sum += i;
		}
	}
	printf("%d %d", count, sum);
	system("pause");
	return 0;
}