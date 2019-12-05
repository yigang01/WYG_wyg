#include<stdio.h>
#include<windows.h>
#include<math.h>
#pragma warning(disable:4996)
#define M 10
void play(int a[],int num)
{
	int left = 0;
	int right = num - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (a[mid] < M)
		{
			left = mid + 1;
		}
		else if (a[mid]>M)
		{
			right = mid - 1;
		}
		else
		{
			printf("%d", mid);
			break;
		}
		if (left > right)
		{
			printf("’“≤ªµΩ!!!\n");
		}
	}
}
int main()
{
	int a[10] = { 1, 2, 5, 6, 8, 9, 10, 14, 25, 89 };
	int num = sizeof(a) / sizeof(a[0]);
	play(a, num);
	system("pause");
	return 0;
}