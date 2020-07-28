#include"game.h"
void Menu()
{
	printf("############################################################\n");
	printf("************************************************************\n");
	printf("************************************************************\n");
	printf("***********        欢迎来到我的游戏大厅        *************\n");
	printf("*********1、三子棋                        2、扫雷***********\n");
	printf("*********                                        ***********\n");
	printf("*********3、猜数字                        4、退出***********\n");
	printf("************************************************************\n");
	printf("************************************************************\n");
	printf("############################################################\n");
	printf("Please Enter select!!!\n");
}
Init_board(char board[][COL], int row, int col)//三子棋棋盘初始化--->全为空
{
	int i = 0;
	int j = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			board[i][j] = ' ';
		}
	}
}
Show_board(char board[][COL], int row, int col)//显示三子棋棋盘
{
	printf("   | 1 | 2 | 3 |\n");
	printf("----------------\n");
	int i = 1;
	int j = 0;
	for (i = 1; i <= row; i++)
	{
		printf(" %d |", i);
		for (j = 0; j < col; j++)
		{
			printf(" %c |", board[i-1][j]);
		}
		printf("\n----------------\n");
	}
}
Computer(char board[][COL], int row, int col)//该三子棋的电脑下棋
{
	while (1)
	{
		int x = rand() % ROW;
		int y = rand() % COL;
		if (board[x][y] == ' ')
		{
			board[x][y] = computer;
			break;
		}
	}
}
Judge(char board[][COL], int row, int col)//在三子棋中判断谁赢谁输
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		if (board[i][0] != ' '&&\
			board[i][0] == board[i][1] && \
			board[i][1] == board[i][2])
			return board[i][0];
	}
	for (i = 0; i < col; i++)
	{
		if (board[0][i] != ' '&&\
			board[0][i] == board[1][i] && \
			board[1][i] == board[2][i])
			return board[0][i];
	}
	if (board[1][1] != ' ' &&\
		board[0][0] == board[1][1] && \
		board[1][1] == board[2][2])
	{
		return board[1][1];
	}
	if (board[1][1] != ' ' &&\
		board[0][2] == board[1][1] && \
		board[1][1] == board[2][0])
	{
		return board[1][1];
	}
	for (i = 0; i < row; i++)
	{
		int j = 0;
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 'N';
			}
		}
	}
	return 'F';
}
void game()//三子棋主要框架
{
	printf(" --------------------------------------- \n");
	printf("| 欢迎来到三子棋游戏，祝你好运，加油!!! |\n");
	printf(" --------------------------------------- \n");
	srand((unsigned long)time(NULL));
	char board[ROW][COL];
	Init_board(board, ROW, COL);//棋盘初始化
	Show_board(board, ROW, COL);//显示棋盘
	char result = 0;
	do
	{
		int x = 0;
		int y = 0;
		printf("请输入<x,y>的坐标:\n");
		scanf("%d %d", &x, &y);
		if (x<0 || x>3 || y<0 || y>3)
		{
			printf("你输入位置有误，请重新输入:\n");
			continue;
		}
		if (board[x - 1][y - 1] != ' ')
		{
			printf("你输入的位置已被占有，请重新输入:\n");
			continue;
		}
		board[x - 1][y - 1] = player;
		result = Judge(board, ROW, COL);//判断结果函数
		Show_board(board, ROW, COL);
		system("cls");
		if (result != 'N')
		{
			break;
		}
		Computer(board, ROW, COL);
		result = Judge(board, ROW, COL);
		Show_board(board, ROW, COL);
		if (result != 'N')
		{
			break;
		}
	} while (1);
	if (result == player)
	{
		printf("恭喜你，你赢了!!!\n");
	}
	else if (result == computer)
	{
		printf("不好意思，你输了!!!\n");
	}
	else
	{
		printf("还不错，平局!!!\n");
	}
	printf("你玩的还不错，要不要再来一把!!!\n");
}
void set_mine(char board[][COL1], int row1, int col1, int *x_p, int *y_p)//扫雷游戏埋雷
{
	int num = 80;
	while (num > 0)
	{
		int x = rand() % (row1 - 2) + 1;
		int y = rand() % (col1 - 2) + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			num--;
		}
	}
	int i = 1;
	int j = 1;
	for (i = 1; i < 11; i++)
	{
		for (j = 1; j < 11; j++)
		{
			if (board[i][j] == '0')
			{
				*x_p = i;
				*y_p = j;
				return;
			}
		}
	}
}
void showboard(char board[][COL1], int row1, int col1)//显示扫雷棋盘
{
	printf("    |");
	int i = 1;
	for (i = 1; i < 11; i++)
	{
		printf(" %d |", i);
	}
	printf("\n");
	printf("--------------------------------------------\n");
	for (i = 1; i < 11; i++)
	{
		printf(" %2d |", i);
		int j = 0;
		for (j = 0; j < 10; j++)
		{
			printf(" %c |", board[i-1][j]);
		}
		printf("\n");
		printf("--------------------------------------------\n");
	}
}
int Getcount(char board[][COL1], int x, int y)//显示周围雷的个数
{
	return board[x - 1][y - 1] + board[x - 1][y] + board[x - 1][y + 1] + board[x][y - 1] + \
		board[x][y + 1] + board[x + 1][y - 1] + board[x + 1][y] + board[x + 1][y + 1] - 8 * '0';
}
void Game()//扫雷
{
	printf(" ------------------------------------- \n");
	printf("| 欢迎来到扫雷游戏，祝你好运，加油!!! |\n");
	printf(" ------------------------------------- \n");
	srand((unsigned long)time(NULL));
	char mine_board[ROW1][COL1];
	char show_board[ROW1][COL1];
	memset(mine_board, '0', sizeof(mine_board));//初始化雷棋盘
	memset(show_board, '*', sizeof(show_board));//初始化用户棋盘
	int no_x = 0;
	int no_y = 0;
	set_mine(mine_board, ROW1, COL1, &no_x, &no_y);//埋雷
	int x = 0;
	int y = 0;
	int time = 80;
	while (time > 0)
	{
		system("cls");
		showboard(show_board, ROW1, ROW1);//显示用户棋盘
		printf("请输入<x,y>的坐标：\n");
		scanf("%d %d", &x, &y);
		if (x <= 0 || x > 10 || y <= 0 || y > 10)
		{
			printf("你输入位置有误，请重新输入:\n");
			continue;
		}
		if (show_board[x-1][y-1] != '*')
		{
			printf("该地方已被排除，请重新输入:\n");
			continue;
		}
		if (mine_board[x-1][y-1] == '1')
		{
			if (time == 80)
			{
				mine_board[x - 1][y - 1] = '0';
				showboard(mine_board, ROW1, COL1);
				break;
			}
		}
		int count = Getcount(mine_board,x, y);//统计该点周围雷的个数
		show_board[x - 1][y - 1] = count + '0';
		time--;
	}
}
void play()//猜数字游戏
{
	int n = rand() % 100 + 1;
	int x = 0;
	do
	{
		printf("请输入你想猜的值:\n");
		scanf("%d", &x);
		if (x > n)
		{
			printf("不好意思，你猜大了!!!\n");
		}
		else if (x < n)
		{
			printf("不好意思，你猜小了!!1\n");
		}
		else
		{
			printf("恭喜你，你猜对了!!!\n");
			break;
		}
	} while (1);
}
void GAme()
{
	printf(" -------------------------------------------- \n");
	printf("|欢迎你来到猜数字游戏,请开始你的表演，加油!!!|\n");
	printf(" -------------------------------------------- \n");
	srand((unsigned long)time(NULL));
	play();
}