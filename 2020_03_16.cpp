#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
typedef struct Node//定义一个节点结构体
{
	int _date;
	struct Node *_next;
}Node;
typedef struct SList//定义一个头节点
{
	Node *head;
}slist;
Node *CreateNode(int date)//构建一个节点，在下列操作中可调用这个函数
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->_date = date;
	node->_next = NULL;
	return node;
}
void Print(slist *sl)//打印链表中的所有元素，在下列操作中可调用这个函数
{
	Node *cur = sl->head;
	while (cur)
	{
		printf("%d ", cur->_date);
		cur = cur->_next;
	}
}
void SListInit(slist *sl)//链表初始化为空
{
	sl->head = NULL;
}
void test(slist *sl)//用头插法先来赋值一些数据，以便于后面操作的检测
{
	int i = 0;
	Node *node = NULL;
	for (i = 5; i > 0; i--)
	{
		node = CreateNode(i);
		if (sl->head == NULL)
		{
			sl->head = node;
		}
		else
		{
			node->_next = sl->head;
			sl->head = node;
		}
	}
	printf("进行以下操作之前链表元素如下\n");
	Print(sl);
	printf("\n");
}
void SListAdd(slist *sl)//在链表中增加一个元素
{
	int x = 0;
	int n = 0;
	printf("请输入你想插入的数#:");
	scanf("%d", &n);
	printf("请输入你想插入哪个数的后面#:");
	scanf("%d", &x);
	Node *cur = sl->head;
	while (cur)
	{
		if (cur->_date == x)
		{
			Node *newnode = CreateNode(n);
			newnode->_next = cur->_next;
			cur->_next = newnode;
		}
		cur = cur->_next;
	}
	Print(sl);
	printf("\n");
}
void SListDel(slist *sl)//删除链表中的一个元素
{
	if (sl->head == NULL)
	{
		printf("链表为空，不能删除!!!\n");
		return;
	}
	else if (sl->head->_next == NULL)
	{
		free(sl->head);
		sl->head = NULL;
		return;
	}
	int x = 0;
	printf("请输入你想删除的数#:");
	scanf("%d", &x);
	Node *cur = sl->head;
	Node *pre = NULL;
	while (cur)
	{
		if (cur->_date == x)
		{
			pre->_next = pre->_next->_next;
			free(cur);
			Print(sl);
			printf("\n");
			return;
		}
		pre = cur;
		cur = cur->_next;
	}
	printf("没有找到你想删除的数!!!\n");
}
void SListChange(slist *sl)//对链表中的一个元素进行修改
{
	if (sl->head == NULL)
	{
		printf("链表为空不能修改!!!\n");
		return;
	}
	int x = 0;
	int n = 0;
	printf("请输入你想修改的元素#:");
	scanf("%d", &x);
	printf("请输入你想把这个元素修改的值#:");
	scanf("%d", &n);
	Node *cur = sl->head;
	while (cur)
	{
		if (cur->_date == x)
		{
			cur->_date = n;
			Print(sl);
			printf("\n");
			return;
		}
		cur = cur->_next;
	}
	printf("没找到你想修改的数!!!\n");
}
void SListcheck(slist *sl)//查找链表中的一个元素
{
	int x = 0;
	printf("请输入你想查找的数#:");
	scanf("%d", &x);
	Node *cur = sl->head;
	while (cur)
	{
		if (cur->_date == x)
		{
			printf("你想查找的数为:%d\n", cur->_date);
			printf("\n");
			return;
		}
		cur = cur->_next;
	}
	printf("没找到\n");
}
int main()
{
	slist sl;
	SListInit(&sl);
	test(&sl);
	int quit = 0;
	int select = 0;
	printf("请输入你想进行的操作#: 1、增  2、删  3、改  4、查  5、退出\n");
	while (!quit)
	{
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			SListAdd(&sl);
			break;
		case 2:
			SListDel(&sl);
			break;
		case 3:
			SListChange(&sl);
			break;
		case 4:
			SListcheck(&sl);
			break;
		case 5:
			quit = 1;
			break;
		}
	}
	system("pause");
	return 0;
}