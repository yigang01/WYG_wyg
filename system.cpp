#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <conio.h> 
#pragma warning(disable:4996)
#define N 100 

struct employee//职工基本情况
{
	char num[6];//编号
	char name[8];//姓名
	char birth[8];//出生年月
	char workplace[10];//工作部门 
	char salarylevel[8];//工资级别
	char position[8];//职称
	char tel[16];//电话
	char sex;//性别f为女m为男
} em[N];


/*主要函数*/


void input();//添加职工信息
void display();//显示职工信息
void save();//保存职工信息
void change();//修改职工信息
void search();
void searchByname();//按姓名查找
void searchBynum();//按编号查找 
void Delete();

int total = 0;//定义total来记数记录数 
int i = 0;

void main(){
	int choice;
	do
	{
		printf("                                        *                \n");//系统欢迎界面 
		printf("                                      *   *                 \n");
		printf("                              * * * *       * * * *            \n");
		printf("                               *                *         \n");
		printf("                         _____欢迎进入职工管理系统_____\n");
		printf("                                   *          *         \n");
		printf("                                  *      *     *       \n");
		printf("                                *   *       *   *       \n");
		printf("                               *                 *     \n");
		printf("                                请您选择操作类型:  \n");
		printf("                           =============================== \n");
		printf("                                 1.添加职工信息\n");//用户选择 
		printf("                                 2.显示职工信息\n");
		printf("                                 3.查找职工信息\n");
		printf("                                 4.修改职工信息\n");
		printf("                                 5.删除职工信息\n");
		printf("                                 0. 退出系统\n");
		printf("                           ================================\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			input();
			break;
		case 2:
			display();
			break;
		case 3:
			search();
			break;
		case 4:
			change();
			break;
		case 5:
			Delete();
			break;
		case 0:
		{
			printf("谢谢使用!再见! ");
			exit(0);//退出系统 
		}
		default:
		{printf("输入有错误请重新输入: ");
		return;
		}
		}
	} while (1);//当为真值时执行do循环
}

void input()
{
	char j = '\0';//初始化j值为空
	do
	{
		total++;
		i++;
		printf("第%d个职工:\n", i);
		printf("请您输入编号: ");//输入编号 
		scanf("%s", em[i].num);
		printf("请您输入姓名: ");//输入姓名
		scanf("%s", em[i].name);
		printf("请您输入性别以(m男f女): ");//输入性别 
		getchar();
		scanf("%c", &em[i].sex);
		printf("请您输入出生年月(格式如：1990.03): ");//输入出生年月 
		scanf("%s", em[i].birth);
		printf("请您输入工作部门: ");//输入工作部门
		scanf("%s", em[i].workplace);
		printf("请您输入职位: ");//输入职位 
		scanf("%s", em[i].position);
		printf("请您输入工资级别: ");//输入工资级 
		scanf("%s", em[i].salarylevel);
		printf("请您输入联系电话: ");//输入联系电话 
		scanf("%s", em[i].tel);
		printf("是否继续输入?(y/n):");
		getchar();
		j = getchar();
		while (j != 'y'&&j != 'n')
		{
			printf("输入不合法\n是否继续输入?(y/n):");
			getchar();
			j = getchar();
		}
	} while (j == 'y');
	save();//保存职工记录
	printf("输入完毕,请按任意键返回\n ");
	getch();//conio库函数里的，结收键盘输入任意~~~  
	return;
}
void save()
{
	FILE *fp;
	int i = 0;
	if ((fp = fopen("employee.txt", "ab")) == NULL)
	{
		printf("cannot open file\n");
		return;
	}
	for (i = 1; i <= total; i++)
	{
		if (fwrite(&em[i], sizeof(struct employee), 1, fp) != 1)
			printf("file write error\n");
	}
	fclose(fp);
}
void display()//显示所有职工信息
{
	FILE *fp;
	int i;
	if ((fp = fopen("employee.txt", "rb")) == NULL)
	{
		printf("文件打开失败或未创建文件！\n");
		return;
	}
	printf("所有职工信息如下: \n");//输出所有职工信息  
	printf("\n===========================================================================\n");
	printf("编号   姓名    性别   出生年月   所在部门    职称    工资级别   联系电话\n");
	printf("===========================================================================\n");
	for (i = 1; fread(&em[i], sizeof(struct employee), 1, fp) != 0; i++)//读完所有数据  
		printf("%-6s%8s%6c%12s%10s%8s%8s%18s\n", em[i].num, em[i].name, em[i].sex, em[i].birth, em[i].workplace, em[i].position, em[i].salarylevel, em[i].tel);
	printf("完毕，请按任意键返回\n ");
	getch();
	fclose(fp);
	return;
}

void search()
{
	int choice;
	printf("请您选择查找方式 ：\n");
	printf("1.按编号查找\n 2.按姓名查找\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:searchBynum(); break;
	case 2:searchByname(); break;
	default:printf("输入有误，请重输入：\n");
	}
}

void searchBynum()
{
	FILE *fp;
	int i;
	char numb[6];
	if ((fp = fopen("employee.txt", "r")) == NULL)
	{
		printf("不能够打开这个文件，请按任意键返回");
		return;
	}
	printf("请您输入要查找的人的编号: ");
	scanf("%s", numb);
	for (i = 0; i<N; i++)//在所有信息中查找符合要求的职工
		if (strcmp(em[i].num, numb) == 0) //找到并显示该职工记录 
		{
		printf("以 下 是 您 要 咨 询 的 人 的 信 息 :\n");
		printf("编号 姓名 性别 出生年月 所在部门 职称 工资级别 联系电话\n");
		printf("*****                                 *****\n");
		printf("%-6s%8s%6c%12s%10s%8s%8s%18s\n", em[i].num, em[i].name, em[i].sex, em[i].birth, em[i].workplace, em[i].position, em[i].salarylevel, em[i].tel);
		printf("查找完毕，请按任意键返回\n ");
		getch();
		fclose(fp);
		return;
		}
	printf("没有这样的人，请按任意键返回\n");
	getch();
	fclose(fp);
	return;
}

void searchByname()
{
	FILE *fp;
	int i = 0;
	char nam[8];
	if ((fp = fopen("employee.txt", "rb")) == NULL)
	{
		printf("不能够打开这个文件，请按任意键返回\n");
		return;
	}
	printf("请您输入要查找的人的姓名: ");
	scanf("%s", nam);
	for (i = 0; i<N; i++)
		if (strcmp(em[i].name, nam) == 0) //找到并显示该职工记录
		{
		printf("以下是您要查询的人的信息:\n ");
		printf("\n===========================================================================\n");
		printf("编号  姓名  性别  出生年月  所在部门  职称  工资级别  联系电话\n");
		printf("===========================================================================\n");
		printf("%-6s%8s%6c%12s%10s%8s%8s%18s\n", em[i].num, em[i].name, em[i].sex, em[i].birth, em[i].workplace, em[i].position, em[i].salarylevel, em[i].tel);
		fclose(fp);
		printf("查找完毕，请按任意键返回\n ");
		getch();
		return;
		}
	printf("没有这样的人，请按任意键返回\n ");
	getch();
	fclose(fp);
	return;
}



void change()
{
	FILE *fp;
	int i;
	char newnum[6];//新编号
	char newname[8];//新名字
	char newsex;//新性别
	char newbirth[8];//新出生年月
	char newworkplace[10];//新工作部门
	char newposition[8];//新职称
	char newsalarylevel[8];//新工资水平 
	char newtel[16];//新电话号码
	char nam[8];
	int choice;
	printf("请您输入要修改的人的姓名: ");
	scanf("%s", &nam);
	if ((fp = fopen("employee.txt", "w+")) == NULL)
	{
		printf("不能够打开这个文件");
		return;
	}
	for (i = 1; i <= N; i++)
		if (strcmp(nam, em[i].name) == 0)
		{
		printf("这是您要修改的个人信息：\n");
		printf("\n===========================================================================\n");
		printf("编号  姓名   性别  出生年月  所在部门    职称   工资级别    联系电话\n");
		printf("=============================================================================\n");
		printf("%-6s%8s%6c%12s%10s%8s%8s%18s\n", em[i].num, em[i].name, em[i].sex, em[i].birth, em[i].workplace, em[i].position, em[i].salarylevel, em[i].tel);
		printf("-----------------------\n ");
		printf("请您选择要修改的部分 : \n");
		printf("=======================\n ");
		printf("1.修改编号\n ");
		printf("2.修改姓名\n ");
		printf("3.修改性别\n ");
		printf("4.修改出生年月\n ");
		printf("5.修改所在部门\n ");
		printf("6.修改职位\n ");
		printf("7.修改工资级别\n ");
		printf("8.修改联系电话\n ");
		printf("0.返回主菜单\n ");
		printf("========================\n ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1: printf("请您输入新的编号: ");
			scanf("%s", newnum);
			strcpy(em[i].num, newnum);
			break;
		case 2: printf("请您输入新的姓名: ");
			scanf("%s", newname);
			strcpy(em[i].name, newname);
			break;
		case 3: printf("请您输入新的性别: ");
			getchar();
			scanf("%c", &newsex);
			em[i].sex = newsex;
			break;
		case 4: printf("请您输入新的出生年月: ");
			scanf("%s", newbirth);
			strcpy(em[i].birth, newbirth);
			break;
		case 5: printf("请您输入新的工作部门: ");
			scanf("%s", newworkplace);
			strcpy(em[i].workplace, newworkplace);
			break;
		case 6:printf("请您输入新的职位: ");
			scanf("%s", newposition);
			strcpy(em[i].position, newposition);
			break;
		case 7:printf("请您输入新的工资级别: ");
			scanf("%s", newsalarylevel);
			strcpy(em[i].salarylevel, newsalarylevel);
			break;
		case 8:printf("请您输入新的联系电话: ");
			scanf("%s", newtel);
			strcpy(em[i].tel, newtel);
			break;
		case 0:
		{
			printf("返回主菜单");
			main();//返回 
		}
		default:printf("输入有错误!请重新输入!"); return;
		}
		printf("\n===========================================================================\n");
		printf("编号     姓名    性别    出生年月    所在部门   职称   工资级别    联系电话\n");
		printf("===========================================================================\n");
		printf("%-6s%8s%6c%12s%10s%8s%8s%18s\n", em[i].num, em[i].name, em[i].sex, em[i].birth, em[i].workplace, em[i].position, em[i].salarylevel, em[i].tel);
		save();//保存修改信息 
		break;
		}
		else if (i == N)
		{
			printf("没有这个职工！\n");
			change();
		}
	printf("\n===================\n");
	printf("1.继续修改\n2.返回主菜单\n");
	printf("===================\n");
	printf("\n请您选择:");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		change();
		break;
	case 2:
		main();
		break;
	default:printf("输入不合法！返回\n"); main();
	}
}
void Delete(){
	FILE *fp;
	if ((fp = fopen("employee.txt", "w+")) == NULL)
	{
		printf("不能够打开这个文件");
		return;
	}
	int i, j;
	char id[6];
	printf("请输入要删除的编号:");
	scanf("%s", id);
	for (i = 0; i<total; i++)
	{
		if (strcmp(id, em[i].num) == 0) 
		{
			for (j = i + 1; j < total; j++)
			{
				em[j - 1] = em[j];
			}
			total--;
			printf("删除成功!\n");
		}
	}
	save();
}
