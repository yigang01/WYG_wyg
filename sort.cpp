#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
typedef int DataType;
void swap(DataType *array, int left, int right)//½»»»Á½¸öÊıµÄÖµ
{
	int temp = array[left];
	array[left] = array[right];
	array[right] = temp;
}
void TreeShiftDown(DataType *array, int n, int parent)//ÏòÏÂµ÷Õû
{
	int child = 2 * parent + 1;
	while (child < n)
	{
		if (child + 1 < n && array[child + 1] > array[child])
		{
			child = child + 1;
		}
		if (array[child] > array[parent])
		{
			swap(array, child, parent);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}
void TreeCreat(DataType *array, int n)//½¨Ê÷
{
	int parent = (n - 2) / 2;
	int i = 0;
	for (i = parent; i >= 0; i--)
	{
		TreeShiftDown(array, n, i);
	}
}
void print(DataType *array, int n)//´òÓ¡
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}
void SortInsert(DataType *array, int n)//²åÈëÅÅĞò
{
	printf("²åÈëÅÅĞò#: ");
	int i = 0;
	for (i = 0; i < n - 1; i++)
	{
		int end = i;
		int key = array[end + 1];
		while (end >= 0 && array[end] > key)
		{
			array[end + 1] = array[end];
			end--;
		}
		array[end + 1] = key;
	}
	print(array, n);
}
void SortShell(DataType *array, int n)//Ï£¶ûÅÅĞò
{
	printf("Ï£¶ûÅÅĞò#: ");
	int grap = n;
	while (grap > 1)
	{
		grap = grap / 3 + 1;
		for (int i = 0; i < n - grap; i++)
		{
			int end = i;
			int key = array[end + grap];
			while (end >= 0 && array[end] > key)
			{
				array[end + 1] = array[end];
				end = end - grap;
			}
			array[end + grap] = key;
		}
	}
	print(array, n);
}
void SortSelect(DataType *array, int n)//Ñ¡ÔñÅÅĞò
{
	printf("Ñ¡ÔñÅÅĞò#: ");
	int i = 0;
	int j = 0;
	for (i = 0; i < n - 1; i++)
	{
		int min =i;
		for (j = i; j < n; j++)
		{
			if (array[j] < array[min])
			{
				min = j;
			}
		}
		swap(array, i, min);
	}
	print(array, n);
}
void SortSelect1(DataType *array, int n)//Ñ¡ÔñÅÅĞòÉı¼¶°æ
{
	printf("Ñ¡ÔñÅÅĞòÉı¼¶°æ#: ");
	int start = 0;
	int end = n - 1;
	int min, max;
	int j = 0;
	while (start < end)
	{
		min = max = start;
		for (j = start + 1; j <= end; j++)
		{
			if (array[j] < array[min])
			{
				min = j;
			}
			if (array[j] >= array[max])
			{
				max = j;
			}
		}
		swap(array, start, min);
		if (max == start)
		{
			max = min;
		}
		swap(array, end, max);
		start++;
		end--;
	}
	print(array, n);
}
void SortBubble(DataType *array, int n)//Ã°ÅİÅÅĞò
{
	printf("Ã°ÅİÅÅĞò#: ");
	int i = 0;
	int j = 0;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - 1 - i; j++)
		{
			if (array[j]>array[j + 1])
			{
				swap(array, j, j + 1);
			}
		}
	}
	print(array, n);
}
void SortHeap(DataType *array, int n)//¶ÑÅÅĞò
{
	printf("¶ÑÅÅĞò#: ");
	TreeCreat(array, n);
	int end = n - 1;
	while (end > 0)
	{
		swap(array, 0, end);
		TreeShiftDown(array, end, 0);
		end--;
	}
	print(array, n);
}
int main()
{
	DataType array[] = { -1, 4, 3, 7, 5, 57, 34 };
	int n = sizeof(array) / sizeof(array[0]);
	SortInsert(array, n);
	SortShell(array, n);
	SortSelect(array, n);
	SortSelect1(array, n);
	SortBubble(array, n);
	SortHeap(array, n);
	system("pause");
	return 0;
}