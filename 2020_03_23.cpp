#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#pragma warning(disable:4996)
typedef int DataType;
typedef struct Stack
{
	DataType *_array;
	int _count;//空间能容纳的总元素
	int _size;//当前元素个数
}Stack;
void stackInit(Stack *st)//栈的初始化
{
	int n = 10;
	st->_array = (DataType *)malloc(sizeof(DataType)*n);
	st->_count = n;
	st->_size = 0;
}
void print(Stack *st)//打印栈的元素，从底向上打印
{
	int count = st->_size;
	st->_size = 0;
	for (st->_size=0; st->_size < count; st->_size++)
	{
		printf("%d ", st->_array[st->_size]);
	}
	st->_size = count;
	printf("\n");
}
void stackInsert(Stack *st)//入栈，尾插
{
	if (st->_size == st->_count)
	{
		st->_array = (DataType *)realloc(st->_array, sizeof(DataType) * 2 * st->_count);
		st->_count = 2 * st->_count;
	}
	int x = 0;
	printf("请输入你想入栈的数字#:");
	scanf("%d", &x);
	st->_array[st->_size] = x;
	st->_size++;
	print(st);
}
void stackDel(Stack *st)//出栈,每出栈一次栈顶元素就少一个
{
	if (st->_size > 0)
	{
		st->_size--;
		print(st);
	}
	else
	{
		printf("出栈错误，栈里已经没有元素了!!!\n");
	}
}
void stackTop(Stack *st)
{
	if (st->_size > 0)
	{
		printf("%d", st->_array[st->_size-1]);
		printf("\n");
	}
	else
	{
		printf("查找失败，栈里没有元素!!!\n");
	}
}
void stackSize(Stack *st)
{
	printf("%d", st->_size);
	printf("\n");
}
void stackEmpty(Stack *st)
{
	if (st->_size == 0)
	{
		printf("此时栈为空!!!\n");
	}
	else
	{
		printf("此时栈不为空!!!\n");
	}
}
void stackDestory(Stack *st)
{
	if (st->_array)
	{
		free(st->_array);
		st->_size = st->_count = 0;
		printf("栈已被销毁!!!\n");
	}
}
int main()
{
	Stack st;
	stackInit(&st);
	int select = 0;
	printf("1、入栈 2、出栈 3、查看栈顶元素 4、查看栈元素个数 5、查看栈是否为空 6、销毁栈 7、退出\n");
	int quit = 0;
	while (!quit)
	{
		printf("请输入你想进行的操作#:");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			stackInsert(&st);
			break;
		case 2:
			stackDel(&st);
			break;
		case 3:
			stackTop(&st);
			break;
		case 4:
			stackSize(&st);
			break;
		case 5:
			stackEmpty(&st);
			break;
		case 6:
			stackDestory(&st);
			break;
		case 7:
			quit = 1;
			break;
		}
	}
	system("pause");
	return 0;
}