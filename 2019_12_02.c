#include<stdio.h>
#include<string.h>
#include<windows.h>
#pragma warning(disable:4996)
#define USER "WYG"
#define PSD "123456"
int main()
{
	int count = 3;
	while (count > 0)
	{
		count--;
		char name[32];
		char passwd[32];
		printf("请输入用户名#:\n");
		scanf("%s", &name);
		printf("请输入密码#:\n");
		scanf("%s", &passwd);
		if (strcmp(USER, name) == 0 && strcmp(PSD, passwd) == 0)
		{
			printf("登录成功\n");
			break;
		}
		else
		{
			printf("用户名和密码输入错误,请重新输入\n");
		}
	}
	system("pause");
	return 0;
}