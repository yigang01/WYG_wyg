#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
int main()
{
	int i = 0;
	int n = 0;
	scanf("%d", &n);
	for (i = 0; i <= n; i++)
	{
		int sum = pow(3, i);
		printf("pow(3,%d) = %d\n", i, sum);
	}
	system("pause");
	return 0;
}