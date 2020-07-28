#include"game.h"
int main()
{
	char name[32];
	char passed[32];
	int count = 3;
	while (count > 0)
	{
		count--;
		printf("*************************\n");
		printf("*欢迎来到我的游戏世界!!!*\n");
		printf("*************************\n");
		printf("\n");
		printf("请输入大佬的名字###:\n");
		scanf("%s", &name);
		printf("请输入密码######:\n");
		scanf("%s", &passed);
		if (strcmp(USER, name) == 0 && \
			strcmp(PSD, passed) == 0)
		{
			printf("输入正确!!!\n");
			break;
		}
		else
		{
			printf("用户名和密码输入错误，请重新输入:\n");
			continue;
		}
		printf("\n");
	}
	if (count > 0)
	{
		printf("登录成功!!!\n");
		int i = 9;
		while (i > 0)
		{
			printf("加载中!!!...................%d\r",i);
			Sleep(1000);
			i--;
		}
		printf("正在加载.........................请稍等!!!\n");
		printf("加载成功!!!\n");
	}
	int quit = 0;
	while (!quit)
	{
		Menu();
		int select = 0;
		printf("请输入你的选择：\n");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			game();//三子棋
			break;
		case 2:
			Game();//扫雷
			break;
		case 3:
			GAme();//猜数字
			break;
		case 4:
			quit = 1;
			break;
		default:
			printf("你选择有误，请重新选择：\n");
			break;
		}
	}
	printf("拜拜了，欢迎下次再玩!!!\n");
	system("pause");
	return 0;
}