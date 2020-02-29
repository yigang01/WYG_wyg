#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
void count(int m, int n)
{
	double sum = 0;
	int i = 0;
	for (i = m; i <= n; i++)
	{
		sum += (i*i + 1.0 / i);
	}
	printf("sum = %.6f", sum);
}
int main()
{
	int n = 0;
	int m = 0;
	scanf("%d %d", &m, &n);
	count(m, n);
	system("pause");
	return 0;
}