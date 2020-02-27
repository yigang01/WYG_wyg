#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
int main()
{
	int i = 0;
	int N = 0;
	double sum = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++)
	{
		sum = sum + (1.0 / i);
	}
	printf("sum = %.6f", sum);
	system("pause");
	return 0;
}