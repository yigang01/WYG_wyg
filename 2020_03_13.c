#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
int main()
{
	int x = 0;
	printf("请输入你想查询的数#:\n");
	scanf("%d", &x);
	int f1 = 0;
	int f2 = 1;
	int f3 = f1 + f2;
	while (1){
		if (x == f2)
		{
			printf("%d", 0);
			break;
		}
		else if (f2 > x)
		{
			if ((f2 - x) > (x-f1))
			{
				printf("%d", x - f1);;				
				break;
			}
			else
			{
				printf("%d", f2 - x);
				break;
			}
		}
		f1 = f2;
		f2 = f3;
		f3 = f1 + f2;
	}
	system("pause");
	return 0;
}