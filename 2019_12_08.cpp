#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
int Small_Public(int A, int B)
{
	int i = 0;
	if (A < B)
	{
		int temp = A;
		A = B;
		B = temp;
	}
	for (i = A; i < A*B; i++)
	{
		if ((i%A) == 0 && (i%B) == 0)
		{
			return i;
		}
	}
}
int main()
{
	int A = 0;
	int B = 0;
	printf("请分别输入A和B的值:\n");
	scanf("%d %d", &A, &B);
	Small_Public(A, B);
	printf("%d", Small_Public(A, B));
	system("pause");
	return 0;
}
