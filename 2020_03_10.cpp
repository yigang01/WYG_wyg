#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
#define NUM 10
typedef int Datetype;
typedef struct SeqList
{
	Datetype *Data;
	size_t count;//顺序表总容量
	size_t size;//顺序表当前占了多少个元素
}seqlist;
void test(seqlist *cp)//给顺序表赋值，以便于对顺序表的增、删、改、查功能进行测试
{
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		cp->Data[i] = i;
		cp->size += 1;
	}
}
void SeqListInit(seqlist *cp)//顺序表初始化
{
	cp->Data = (Datetype*)malloc(sizeof(seqlist) * NUM);
	if (cp->Data == NULL)
	{
		printf("申请空间失败!!!\n");
		exit(1);
	}
	cp->count = NUM;
	cp->size = 0;
}
void SeqListAdd(seqlist *cp)//顺序表增加元素
{
	size_t value = 0;
	size_t pos = 0;
	size_t i = 0;
	printf("请输入你要插入的数#:");
	scanf("%d", &value);
	printf("请选择你想插入的位置#:");
	scanf("%d", &pos);
	for (i = cp->size; i > pos; i--)
	{
		cp->Data[i] = cp->Data[i - 1];
	}
	cp->Data[pos] = value;
	cp->size += 1;
	for (i = 0; i < cp->size; i++)
	{
		printf("%d ", cp->Data[i]);
	}
	printf("\n");
}
void SeqListDel(seqlist *cp)//顺序表查找
{
	size_t pos = 0;
	size_t i = 0;
	printf("请输入你想要删除的位置#:");
	scanf("%d", &pos);
	if (pos >= 0 && pos <= cp->size - 1)
	{
		for (i = pos + 1; i < cp->size; i++)
		{
			cp->Data[i - 1] = cp->Data[i];
		}
		cp->size -= 1;
		for (i = 0; i < cp->size; i++)
		{
			printf("%d ", cp->Data[i]);
		}
		printf("\n");
	}
}
void SeqListCheck(seqlist *cp)//顺序表查找
{
	size_t pos = 0;
	printf("请输入你想查找的位置#:");
	scanf("%d", &pos);
	printf("%d", cp->Data[pos]);
	printf("\n");
}
void SeqListChange(seqlist *cp)//顺序表修改
{
	size_t value = 0;
	size_t pos = 0;
	size_t i = 0;
	printf("请输入你想改的数据#:");
	scanf("%d", &value);
	printf("请输入你想改的位置#:");
	scanf("%d", &pos);
	cp->Data[pos] = value;
	for (i = 0; i < cp->size; i++)
	{
		printf("%d ", cp->Data[i]);
	}
	printf("\n");
}
int main()
{
	seqlist cp;
	SeqListInit(&cp);
	test(&cp);
	int quit = 0;
	while (!quit)
	{
		printf("请输入你想要选择的操作# 1、增  2、删  3、查  4、改  5、退出:\n");
		int select = 0;
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			SeqListAdd(&cp);
			break;
		case 2:
			SeqListDel(&cp);
			break;
		case 3:
			SeqListCheck(&cp);
			break;
		case 4:
			SeqListChange(&cp);
			break;
		case 5:
			quit = 1;
			break;
		}
	}
	system("pause");
	return 0;
}