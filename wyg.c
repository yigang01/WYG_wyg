#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
int main()
{
	int i = 0;
	int j = 0;
	int sum = 0;
	int ret = 1;
	int n = 0;
	printf("ÇëÊäÈënµÄÖµ:\n");
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= i; j ++)
		{
			ret *= j;
		}
		sum += ret;
		ret = 1;
	}
	printf("%d", sum);
	system("pause");
	return 0;
}