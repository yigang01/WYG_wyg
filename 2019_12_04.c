#include<stdio.h>
#include<time.h>
#include<string.h>
#include<windows.h>
#pragma warning(disable:4996)
#define USER "WYG"
#define PSD "123456"
Menu()
{
	printf("***************************************************\n");
	printf("*******           猜数字游戏             **********\n");
	printf("********1、play                   2、Exit**********\n");
	printf("***************************************************\n");
}
play()
{
	int n = 0;
	int count = 0;
	int x = rand() % 100 + 1;
	do
	{
		printf("请输入你想猜的数字:\n");
		scanf("%d", &n);
		if (x > n)
		{
			printf("你猜小了\n");
			count++;
		}
		else if (x < n)
		{
			printf("你猜大了\n");
			count++;
		}
		else
		{
			printf("你猜对了\n");
			break;
		}
	} while (1);
	printf("你总共猜了%d次", count + 1);
}
int main()
{
	char name[16];
	char passwd[16];
	int count = 3;
	while (count > 0)
	{
		count--;
		printf("请输入用户名#:\n");
		scanf("%s", &name);
		printf("请输入密码#:\n");
		scanf("%s", &passwd);
		if (strcmp(USER, name) == 0 && strcmp(PSD, passwd) == 0)
		{
			printf("账号密码输入正确\n");
			break;
		}
		else
		{
			printf("账号或密码输入错误，请重新输入\n");
		}
		printf("你还有%d次机会", count);
	}
	int quit = 0;
	while (!quit)
	{
		srand((unsigned long)time(NULL));
		Menu();
		int select = 0;
		printf("请输入你的选择:\n");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			play();
		case 2:
			quit = 1;
			break;
		default:
			printf("选择错误,请重新选择:\n");
			continue;
		}
	}
	return 0;
}