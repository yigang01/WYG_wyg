//作者：王义钢
//班级：网络工程1801
//时间：2019_12_25
//题目：利用随机函数产生30000个随机整数，进行顺序查找、折半查找
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)
#define MAX 10
void OrderFind(int a[], int num)
{
	clock_t start;
	clock_t finish;
	double time;
	int i = 0;
	start = clock();
	for (i = 0; i < MAX; i++)
	{
		if (a[i] == num)
		{
			printf("通过顺序查找找到该数据%d\n", a[i]);
			break;
		}
	}
	if (i == MAX)
	{
		printf("顺序查找未找到该数据\n");
		return;
	}
	finish = clock();
	time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("该顺序查找所用时间为%f\n", time);
}
void HalfFind(int a[], int num)
{
	clock_t start = 0;
	clock_t finish;
	double time;
	int left = 0;
	int right = MAX - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (a[mid] < num)
		{
			left = mid + 1;
		}
		else if (a[mid]>num)
		{
			right = mid - 1;
		}
		else
		{
			printf("该数据已被找到为%d\n", a[mid]);
			break;
		}
		if (left > right)
		{
			printf("该数据未找到\n");
			return;
		}
	}
	finish = clock();
	time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("该折半查找所用时间为%f\n", time);
}
int main()
{
	srand((unsigned long)time(NULL));
	printf("******************************************\n");
	printf("*******       1-->顺序查找         *******\n");
	printf("*******       2-->折半查找         *******\n");
	printf("*******       3-->退出             *******\n");
	int a[MAX] = { 0 };
	int i = 0;
	for (i = 0; i < MAX; i++)
	{
		a[i] = rand() % 10 + 1;
	}
	printf("随即生成的30000个数为\n");
	for (i = 0; i < MAX; i++)
	{
		printf("%d ", a[i]);
	}
	int num = rand() % 10 + 1;//随机生成的一个待查数
	printf("随机生成的数据为%d\n", num);
	int quit = 0;
	while (!quit)
	{
		int select = 0;
		printf("请输入你的选择#\n");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			OrderFind(a, num);
			break;
		case 2:
			HalfFind(a, num);
			break;
		case 3:
			quit = 1;
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}