#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
typedef struct Node//一个节点
{
	struct Node* _next;
	int _data;
}Node;
typedef struct Queue//队列
{
	Node *_front;//头节点
	Node *_rear;//尾节点
	int size;//元素个数
}Queue;
void queueInit(Queue *q)//初始化队列
{
	q->_front = q->_rear = NULL;
	q->size = 0;
}
void print(Queue *q)
{
	Node *cur = q->_front;
	while (cur)
	{
		printf("%d ", cur->_data);
		cur = cur->_next;
	}
}
void queueInsert(Queue *q)//入队,从队头向队尾打印
{
	int x = 0;
	printf("请输入你想入队的元素#:");
	scanf("%d", &x);
	Node *node = (Node *)malloc(sizeof(Node));
	node->_data = x;
	node->_next = NULL;
	if (q->_front == NULL)
	{
		q->_front = q->_rear = node;
		q->size++;
	}
	else
	{
		q->_rear->_next = node;
		q->_rear = node;
		q->size++;
	}
	print(q);
	printf("\n");
}
void queueDel(Queue *q)//出队
{
	if (q->_front != NULL)
	{
		Node *next = q->_front->_next;
		free(q->_front);
		q->_front = next;
		print(q);
	}
	else
	{
		q->_rear = NULL;
		printf("此时队列为空,不可进行出队操作!!!\n");
	}
	q->size--;
}
void queueTop(Queue *q)
{
	printf("%d", q->_front->_data);
}
void queueRear(Queue *q)
{
	printf("%d", q->_rear->_data);
}
void queueEmpty(Queue *q)
{
	if (q->_front == NULL)
	{
		printf("此时队列为空!!!\n");
	}
	else
	{
		printf("此时队列不为空!!!\n");
	}
}
void queueSize(Queue *q)
{
	printf("%d", q->size);
}
void queueDistory(Queue *q)
{
	Node *cur = q->_front;
	Node *next = q->_front;
	while(cur)
	{
		next = q->_front->_next;
		free(q->_front);
		q->_front = next;
		cur = next;
	}
	printf("此队列已被销毁!!!\n");
}
int main()
{
	Queue q;
	queueInit(&q);
	int select = 0;
	int quit = 0;
	printf("1、入队 2、出队 3、查看队头元素 4、查看队尾元素 5、判读队列是否为空 6、查看对列元素个数 7、销毁队列 8、退出\n");
	while (!quit)
	{
		printf("请输入你想进行的操作#:");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			queueInsert(&q);
			break;
		case 2:
			queueDel(&q);
			break;
		case 3:
			queueTop(&q);
			break;
		case 4:
			queueRear(&q);
			break;
		case 5:
			queueEmpty(&q);
			break;
		case 6:
			queueSize(&q);
			break;
		case 7:
			queueDistory(&q);
			break;
		case 8:
			quit = 1;
			break;
		}
	}
}