#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#pragma warning(disable:4996)
int main()
{
	int x = 20;
	int y = 20;
	int i = 0;
	int j = 0;
	int nx = 5;
	int killed = 0;
	int isFird = 0;
	char input;
	while (1)
	{
		system("cls");
		if (killed == 0)
		{
			for (i = 0; i < nx; i++)
			{
				printf("  ");
			}
			printf("+");
		}
		if (isFird == 0)
		{
			for (i = 0; i < y; i++)
			{
				printf("\n");
			}
		}
		else
		{
			for (i = 0; i < y; i++)
			{
				for (j = 0; j < x; j++)
				{
					printf("  ");
				}
				printf("   |\n");
			}
			if ((x + 3) == nx)
			{
				killed = 1;
			}
			isFird = 0;
		}
		for (i = 0; i < x; i++)
		{
			printf("  ");
		}
		printf("   *\n");
		for (i = 0; i < x; i++)
		{
			printf("  ");
		}
		printf("*******\n");
		for (i = 0; i < x; i++)
		{
			printf("  ");
		}
		printf(" *****\n");
		for (i = 0; i < x; i++)
		{
			printf("  ");
		}
		printf("  * *\n");
		input = getch();
		if (input == 'w')
		{
			y--;
		}
		else if (input == 's')
		{
			y++;
		}
		else if (input == 'a')
		{
			x--;
		}
		else if (input == 'd')
		{
			x++;
		}
		else if (input == ' ')
		{
			isFird = 1;
		}
		else
		{
			printf("输入错误，请重新输入!!!\n");
			continue;
		}
	}
	system("pause");
	return 0;
}