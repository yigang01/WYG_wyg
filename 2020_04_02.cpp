#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
typedef char DataType;
typedef struct Node//定义一个结点
{
	struct Node *_left;
	struct Node *_right;
	DataType _data;
}Node;
typedef struct BinaryTree//定义树
{
	Node *root;
}BinaryTree;
Node *Treecreat(DataType *array, int *idx)//用前序遍历创建一个二叉树
{
	if (array[*idx] != '#')
	{
		Node *root = (Node *)malloc(sizeof(Node));
		root->_data = array[*idx];
		(*idx)++;
		root->_left = Treecreat(array, idx);
		(*idx)++;
		root->_right = Treecreat(array, idx);
		return root;
	}
	else
	{
		return NULL;
	}
}
void InOrder(Node *root)
{
	if (root)
	{
		InOrder(root->_left);
		printf("%c ", root->_data);
		InOrder(root->_right);
	}
}
int main()
{
	DataType array[100];
	int idx = 0;
	scanf("%s", array);
	Node *root = Treecreat(array, &idx);
	InOrder(root);
	system("pause");
	return 0;
}
