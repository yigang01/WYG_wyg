#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
typedef struct heap
{
	int *_array;
	int _size;//当前个数
	int _count;//总容量
}heap;
void swap(int *arr, int child, int parent)//交换两个堆节点
{
	int temp = arr[child];
	arr[child] = arr[parent];
	arr[parent] = temp;
}
void print(heap *hp)//打印堆
{
	int i = 0;
	for (i = 0; i < hp->_size; i++)
	{
		printf("%d ", hp->_array[i]);
	}
}
void heapShiftDown(int *arr, int size, int parent)//从父节点向下调整
{
	int child = 2 * parent + 1;//先找到左孩子
	while (child  < size)
	{
		if (child + 1 <size &&  arr[child] < arr[child + 1])
		{
			child += 1;
		}
		if (arr[child] > arr[parent])
		{
			swap(arr, child, parent);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}
void heapInit(heap *hp, int *arr, int size)//堆的初始化，相当于构建一个堆
{
	int i = 0;
	int j = (size - 2) / 2;
	hp->_array = (int *)malloc(sizeof(int)*size);//开辟数组大小个空间
	memcpy(hp->_array, arr, sizeof(int)*size);//把数组里的内容拷贝到开辟的堆空间里
	hp->_size = hp->_count = size;
	for (i = j; i >= 0; i--)
	{
		heapShiftDown(hp->_array, size, i);
	}
	print(hp);
}
void heapShiftUp(int *arr, int child)//从孩子节点向上调整
{
	int parent = (child - 1) / 2;
	while (child > 0)//while(parent>=0)也可以
	{
		if (arr[child] > arr[parent])
		{
			swap(arr, child, parent);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}
void heapInster(heap *hp,int *arr)//入堆
{
	if (hp->_count == hp->_size)//如果当前元素个数等于最大容量，此时需要扩容
	{
		hp->_count = 2 * hp->_count;
		hp->_array = (int *)realloc(hp->_array,sizeof(int)*(hp->_count));
	}
	int value = 0;
	printf("请输入你想插入的值#:");
	scanf("%d", &value);
	hp->_array[hp->_size] = value;
	hp->_size++;
	heapShiftUp(hp->_array, hp->_size - 1);
	print(hp);
	printf("\n");
}
void heapDel(heap *hp)//出堆
{
	if (hp->_size == 0)
	{
		printf("此时堆为空，不能出堆!!!\n");
	}
	else
	{
		hp->_array[0] = hp->_array[hp->_size - 1];
		hp->_size--;
		heapShiftDown(hp->_array, hp->_size, 0);
		print(hp);
		printf("\n");
	}
}
void heapTop(heap *hp)//查看堆顶元素
{
	printf("%d", hp->_array[0]);
	printf("\n");
}
void heapSize(heap *hp)//查看堆元素个数
{
	printf("%d", hp->_size);
	printf("\n");
}
void heapEmpty(heap *hp)//判断堆是否为空
{
	if (hp->_size == 0)
	{
		printf("此时堆为空!!!\n");
	}
	else
	{
		printf("此时堆不为空!!!\n");
	}
}
int main()
{
	heap hp;
	int arr[] = { 20, 40, 8, 56, 90, 4, 67, 23, 45, 60 };
	int size = sizeof(arr) / sizeof(arr[0]);
	printf("已创建好的堆如下:  ");
	heapInit(&hp, arr, size);
	printf("\n");
	printf("1、入堆  2、出堆  3、查看堆顶元素  4、查看堆元素个数  5、判空  6、退出\n");
	int select = 0;
	int quit = 0;
	while (!quit)
	{
		printf("请输入你想进行的操作#:");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			heapInster(&hp, arr);
			break;
		case 2:
			heapDel(&hp);
			break;
		case 3:
			heapTop(&hp);
			break;
		case 4:
			heapSize(&hp);
			break;
		case 5:
			heapEmpty(&hp);
			break;
		case 6:
			quit = 1;
			break;
		}
	}
	system("pause");
	return 0;
}



