#include<iostream>
using namespace std;
template<class T>
struct AVLNode
{
	int _bf;
	T _val;
	AVLNode<T> *_left;
	AVLNode<T> *_right;
	AVLNode<T> *_parent;
	AVLNode(const T& val = T())
		:_val(val)
		, _bf(0)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{}
};
template<class T>
class AVLtree
{
public:
	typedef AVLNode<T> Node;
	AVLtree(Node *root = nullptr)
		:_root(root)
	{}
	bool insert(const T& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}
		Node *parent = nullptr;
		Node *cur = _root;
		while (cur)
		{
			parent = cur;
			if (cur->_val == val)
			{
				return false;
			}
			else if (cur->_val < val)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
		}
		cur = new Node(val);
		if (parent->_val < val)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;
		//1、调整
		while (parent)
		{
			//平衡因子更新
			if (parent->_left == cur)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			//判断是否继续更新和调整
			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == -1 || parent->_bf == 1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (abs(parent->_bf) == 2)
			{
				//需要旋转整棵树
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					//左边的左边高，进行右旋
					RotateR(parent);
					cout << "节点：" << parent->_val << "右旋" << endl;
				}
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					//右边的右边高，进行左旋
					RotateL(parent);
					cout << "节点：" << parent->_val << "左旋" << endl;
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					//左边的右边高，进行左右双旋
					RotateL(cur);
					RotateR(parent);
					cout << "节点：" << cur->_val << " " << parent->_val << "左右双旋" << endl;
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					//右边的左边高
					RotateR(cur);
					RotateL(parent);
					cout << "节点：" << cur->_val << " " << parent->_val << "右左双旋" << endl;
				}
				break;
			}
		}
		return true;
	}
	void RotateR(Node *parent)//右旋
	{
		Node *subL = parent->_left;
		Node *subLR = subL->_right;
		subL->_right = parent;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			Node *pp = parent->_parent;
			subL->_parent = pp;
			if (pp->_left == parent)
			{
				pp->_left = subL;
			}
			else
			{
				pp->_right = subL;
			}
			parent->_parent = subL;
		}
		subL->_bf = parent->_bf = 0;
	}
	void RotateL(Node *parent)//左旋
	{
		Node *subR = parent->_right;
		Node *subRL = subR->_left;
		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		if (parent == _root)
		{
			_root = subR;
			subR->_parent == nullptr;
		}
		else
		{
			Node *pp = parent->_parent;
			subR->_parent = pp;
			if (pp->_left == parent)
			{
				pp->_left = subR;
			}
			else
			{
				pp->_right = subR;
			}
		}
		parent->_parent = subR;
		subR->_bf = parent->_bf = 0;
	}
	void inorder()
	{
		_inorder(_root);
		cout << endl;
	}
	void _inorder(Node *root)
	{
		if (root)
		{
			_inorder(root->_left);
			cout << root->_val << " ";
			_inorder(root->_right);
		}
	}
	bool isBalance()
	{
		return _isBalance(_root);
	}
	bool _isBalance(Node *root)
	{
		if (root == nullptr)
		{
			return true;
		}
		int left = Height(root->_left);
		int right = Height(root->_right);
		if (right - left != root->_bf)
		{
			cout << "节点：" << root->_val << "异常：高度差" << right - left << "!=bf" << root->_bf << endl;
			return false;
		}
		return abs(root->_bf) < 2
			&& _isBalance(root->_left)
			&& _isBalance(root->_right);
	}
	int Height(Node *root)
	{
		if (root == nullptr)
		{
			return 0;
		}
		int left = Height(root->_left);
		int right = Height(root->_right);
		return left > right ? left + 1 : right + 1;
	}
private:
	Node *_root;
};
void test()
{
	AVLtree<int> avl;
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (const auto&a : array)
	{
		avl.insert(a);
	}
	avl.inorder();
}
int main()
{
	test();
	system("pause");
	return 0;
}