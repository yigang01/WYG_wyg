#include<iostream>
using namespace std;
template<class T>
struct ListNode//定义一个节点
{
	T _value;
	ListNode<T> *_next;
	ListNode<T> *_prev;
	ListNode(const T&val=T())
		:_value(val)
		, _next(nullptr)
		, _prev(nullptr)
	{}
};

//封装节点构造一个迭代器
template<class T,class Ref,class Ptr>
struct Listiterator
{
	typedef ListNode<T> Node;
	typedef Listiterator<T,Ref,Ptr> self;
	Node *_node;
	Listiterator(Node *node)
		:_node(node)
	{}
	Ref& operator*()//迭代器的解引用
	{
		return _node->_value;
	}
	self& operator++()//移动到下一个节点
	{
		_node = _node->_next;
		return *this;
	}
	self& operator--()//移动到上一个节点
	{
		_node = _node->_prev;
		return *this;
	}
	bool operator!=(const self& it)//判断两个节点是否相等
	{
		return _node != it._node;
	}
	Ptr operator->()//->运算符重载
	{
		return &_node->_value;
	}
};

//用带头双向循环链表
template<class T>
class List
{
public:
	typedef Listiterator<T,T&,T*> iterator;
	typedef Listiterator<T, const T&, const T*> const_iterator;
	typedef ListNode<T> Node;
	List()//无参构造函数
		:_header(new Node)
	{
		_header->_prev = _header->_next = _header;
	}
	void pushBack(const T& val)//尾插一个值
	{
		Node *prev = _header->_prev;
		Node *newNode = new Node(val);
		prev->_next = newNode;
		newNode->_prev = prev;
		newNode->_next = _header;
		_header->_prev = newNode;
	}
	void insert(iterator pos, const T& val)//任意位置插入一个值
	{
		Node *prev = pos._node->_prev;
		Node *newNode = new Node(val);
		prev->_next = newNode;
		newNode->_prev = prev;
		newNode->_next = pos._node;
		pos._node->_prev = newNode;
	}
	void pushFront(const T& val)//头插
	{
		insert(begin(), val);
	}
	void popFront()//头删
	{
		erase(begin());
	}
	void popBack()//尾删
	{
		erase(--end());
	}
	iterator erase(iterator pos)//删除任意位置
	{
		if (pos != end())
		{
			Node *prev = pos._node->_prev;
			Node *next = pos._node->_next;
			Node *curNode = pos._node;
			delete curNode;
			prev->_next = next;
			next->_prev = prev;
			return iterator(next);
		}
		return pos;
	}
	iterator begin()
	{
		return iterator(_header->_next);
	}
	iterator end()
	{
		return iterator(_header);
	}
	const_iterator cbegin() const
	{
		return const_iterator(_header->_next);
	}
	const_iterator cend() const
	{
		return const_iterator(_header);
	}
	void clear()
	{
		Node *start = _header->_next;
		while (start != _header)
		{
			Node *next = start->_next;
			delete start;
			start = next;
		}
	}
	~List()
	{
		if (_header)
		{
			clear();
			delete _header;
			_header = nullptr;
		}
	}
private:
	Node *_header;
};
void test()
{
	List<int> str1;
	str1.pushBack(1);
	str1.pushBack(2);
	str1.pushBack(3);
	str1.pushBack(4);
	str1.pushFront(10);
	str1.popFront();
	str1.popBack();
	List<int>::const_iterator cit = str1.cbegin();
	while (cit != str1.cend())
	{
		cout << *cit << " ";
		++cit;
	}
	cout << endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}