#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
int Prime(int x)
{
	int i = 0;
	for(i = 2; i < x; i++)
	{
		if (x%i != 0)
		{
			return 1;//1表示是素数
			break;
		}
		else
		{
			return 0;//0表示不是素数
			break;
		}
	}
}
int main()
{
	int x = 0;
	printf("Please Enter x \n ");
	scanf("%d", &x);
	int z = Prime(x);
	printf("%d", z);
	system("pause");
	return 0;
}