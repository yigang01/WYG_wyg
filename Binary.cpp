#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
//定义一个栈可以实现入栈出栈获取栈顶元素的操作
#define num 10
typedef char BDataType;
typedef struct Node//定义树的一个节点
{
	struct Node *_left;
	struct Node *_right;
	BDataType _data;
}Node;
typedef Node* SDataType;
typedef struct stack//定义栈
{
	SDataType *_array;
	int _count;//总容量大小
	int _size;//当前元素大小
}stack;
void stackInit(stack *st)//栈的初始化
{
	st->_array = (SDataType*)malloc(sizeof(SDataType)*num);
	st->_count = num;
	st->_size = 0;
}
void stackInsert(stack *st, SDataType value)//入栈
{
	if (st->_size == st->_count)//空间已满，需要扩容
	{
		st->_array = (SDataType*)realloc(st->_array, sizeof(SDataType)*(2 * st->_count));
		st->_count = 2 * st->_count;
	}
	st->_array[st->_size] = value;
	st->_size++;
}
void stackDel(stack *st)//出栈
{
	if (st->_size == 0)
	{
		printf("栈以为空，不能出栈!!!\n");
	}
	st->_size--;
}
 SDataType stackTop(stack *st)//获取栈顶元素
{
	 return st->_array[st->_size - 1];
}
int stackEmpty(stack *st)//判断栈是否为空
{
	if (st->_size == 0)
	{
		return 1;
	}
	return 0;
}
//用栈来实现二叉树的非递归的三种遍历方法
//先创建一个树
Node *TreeCreat(BDataType *array, int *pos)//创建一棵树，后面会对这棵树进行各种排序
{
	if (array[*pos] != '#')
	{
		Node *root = (Node *)malloc(sizeof(Node));
		root->_data = array[*pos];
		(*pos)++;
		root->_left = TreeCreat(array, pos);
		(*pos)++;
		root->_right = TreeCreat(array, pos);
		return root;
	}
	else
	{
		return NULL;
	}
}
//1、前序遍历
void preOrder(Node *root)//前序遍历非递归
{
	printf("前序遍历#: ");
	stack st;
	stackInit(&st);
	Node *cur = root;
	Node *top;
	while (cur || stackEmpty(&st) != 1)
	{
		while (cur)
		{
			printf("%c ", cur->_data);
			stackInsert(&st, cur);
			cur = cur->_left;
		}
		top = stackTop(&st);
		stackDel(&st);
		cur = top->_right;
	}
	printf("\n");
}
//2、中序遍历
void MidOrder(Node *root)//中序遍历非递归
{
	printf("前序遍历#: ");
	stack st;
	stackInit(&st);
	Node *cur = root;
	Node *top;
	while (cur || stackEmpty(&st) != 1)
	{
		while (cur)
		{
			stackInsert(&st, cur);
			cur = cur->_left;
		}
		top = stackTop(&st);
		stackDel(&st);
		printf("%c ", top->_data);
		cur = top->_right;
	}
	printf("\n");
}
//3、后序遍历
void EndOrder(Node *root)//后序遍历非递归
{
	printf("前序遍历#: ");
	stack st;
	stackInit(&st);
	Node *cur = root;
	Node *top;
	Node *prev = NULL;
	while (cur || stackEmpty(&st) != 1)
	{
		while (cur)
		{
			stackInsert(&st, cur);
			cur = cur->_left;
		}
		top = stackTop(&st);
		if (top->_right == NULL || top->_right == prev)
		{
			printf("%c ", top->_data);
			stackDel(&st);
			prev = top;
		}
		else
		{
			cur = top->_right;
		}
	}
	printf("\n");
}
int main()
{
	BDataType array[100];//定义一个char数组
	scanf("%s", array);
	int pos = 0;
	Node *root = TreeCreat(array, &pos);
	preOrder(root);//前序遍历
	MidOrder(root);//中序遍历
	EndOrder(root);//后序遍历
	system("pause");
	return 0;
}


