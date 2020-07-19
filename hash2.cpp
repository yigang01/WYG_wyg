#include<iostream>
#include<vector>
#include<string>
using namespace std;
template<class K>
struct keyofvalue
{
	const K& operator()(const K& key)
	{
		return key;
	}
};
template<class V>
struct hashNode
{
	V _val;
	hashNode<V> *_next;
	hashNode(const V& value = V())
		:_val(value)
		, _next(nullptr)
	{}
};
template<class K, class V, class keyofvalue>//前置声名
class hashTable;
template<class K,class V,class keyofvalue>
struct hashiterator//封装一个迭代器
{
	typedef hashNode<V> Node;
	Node *_node;
	typedef hashTable<K, V, keyofvalue> HT;
	typedef hashiterator<K, V, keyofvalue> self;
	HT *_ht;
	hashiterator(Node *node,HT *ht)
		:_node(node)
		, _ht(ht)
	{}
	V& operator*()
	{
		return _node->_val;
	}
	V& operator->()
	{
		return &_node->_val;
	}
	bool operator!=(const self& it)
	{
		return _node != it._node;
	}
	self& operator++(int)
	{
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			//找到下一个非空链表的头节点
			//1、定位当前节点在哈希表中的位置
			keyofvalue kov;
			size_t idx = kov(_node->_val) % _ht->_table.size();
			++idx;
			Node *cur = _ht->_table[idx];
			for (; idx < _ht->_table.size(); idx++)
			{
				if (_ht->_table[idx])
				{
					_node = _ht->_table[idx];
					break;
				}
			}
			if (idx == _ht->_table.size())
			{
				_node = nullptr;
			}
		}
		return *this;
	}
};
template<class K,class V,class keyofvalue>
class hashTable
{
public:
	template<class K, class V, class keyofvalue>
	friend struct hashiterator;
	typedef hashNode<V> Node;
	hashTable(int n = 10)//默认构造
	{
		_size = n;
		_table.resize(n);
	}
	typedef hashiterator<K, V, keyofvalue> iterator;
	iterator begin()
	{
		for (int i = 0; i < _table.size(); i++)
		{
			Node *cur = _table[i];
			if (cur)
			{
				return iterator(cur,this);
			}
		}
		return iterator(nullptr,this);
	}
	iterator end()
	{
		return iterator(nullptr,this);
	}
	bool insert(const V& value)//插入
	{
		//1、检查容量
		//checkcapacity()
		//2、计算位置
		keyofvalue kov;
		size_t idx = kov(value) % _table.size();
		//3、搜索key是否已经存在
		Node *cur = _table[idx];
		while (cur)
		{
			if (kov(cur->_val) == kov(value))
			{
				return false;
			}
			cur = cur->_next;
		}
		//找到了，进行头插
		cur = new Node(value);
		cur->_next = _table[idx];
		_table[idx] = cur;
		_size++;
		return true;
	}
	void checkcapacity()//检查容量
	{
		if (_size == _table.size())
		{
			size_t newSize = _size == 0 ? 5 : 2 * _table.szie();
			vector<Node*> newHt;
			newHt.resize(newSize);
			keyofvalue kov;
			//遍历旧表中的非空链表
			int i = 0;
			for (i = 0; i < _table.size(); i++)
			{
				Node *cur = _table[i];
				while (cur)
				{
					Node *next = cur->_next;
					//计算新的位置
					size_t idx = kov(cur->_val) % newHt.size();
					//头插
					cur->_next = newHt[idx];
					newHt[idx] = cur;
					//处理下一个元素
					cur = next;
				}
			}
			_table.swap(newHt);
		}
	}
	Node *find(const K& key)//查找
	{
		if (_table.size() == 0)
		{
			return nullptr;
		}
		size_t idx = key % _table.size();
		Node *cur = _table[idx];
		keyofvalue kov;
		while (cur)
		{
			if (kov(cur->_val) == key)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return nullptr;
	}
	bool erase(const K& key)//删除
	{
		size_t idx = key % _table.size();
		Node *cur = _table[idx];
		Node *prve = nullptr;
		keyofvalue kov;
		while (cur)
		{
			if (kov(cur->_val) == key)
			{
				//删除，判断删除的是不是头节点
				if (prve == nullptr)
				{
					_table[idx] = cur->_next;
				}
				else
				{
					prve->_next = cur->_next;
				}
				delete cur;
				cur = nullptr;
				_size--;
				return true;
			}
			else
			{
				prve = cur;
				cur = cur->_next;
			}
		}
		return false;
	}
private:
	vector<Node*> _table;
	size_t _size;
};
//字符转整数的仿函数
struct strtoint
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto& ch : str)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};
template < class K >
struct hashfun
{
	size_t operator()(const k& key)
	{
		return key;
	}
};
template<class K,class V>
class unorderedmap
{
	struct mapkeyofvalue
	{
		const K& operator()(const pair<K, V>&  value)
		{
			return value.first;
		}
	};
public:
	typedef hashNode<V> Node;
	bool insert(const pair<K, V>& value)
	{
		return _ht.insert(value);
	}
	bool erase(const pair<K, V>& value)
	{
		_ht.erase(value.first);
	}
	Node *find(const pair<K, V>& value)
	{
		_ht.find(value.first);
	}
private:
	hashTable<K, V, mapkeyofvalue> _ht;
};
template<class K,class HF = hashfun<K>>
class unorderset
{
	struct setkeyofvalue
	{
		const K& operator()(const K& value)
		{
			return value;
		}
	};
public:
	typedef typename hashTable<K, K, setkeyofvalue>::iterator iterator;
	iterator begin()
	{
		return _ht.begin();
	}
	iterator end()
	{
		return _ht.end();
	}
	bool insert(const K& value)
	{
		return _ht.insert(value);
	}
private:
	hashTable<K, K, setkeyofvalue> _ht;
};
void test()
{
	hashTable<int, int, keyofvalue<int>> str;
	str.insert(10);
	str.insert(20);
	str.insert(30);
	str.insert(110);
	str.insert(70);
	str.insert(60);
	str.insert(90);
	str.insert(80);
	hashTable<int, int, keyofvalue<int>>::iterator it = str.begin();
	while (it != str.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
void test1()
{
	unorderset<int> str;
	str.insert(1);
	str.insert(8);
	str.insert(73);
	str.insert(44);
	str.insert(5);
	unorderset<int>::iterator it = str.begin();
	while (it != str.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
void test2()
{
	unorderset<string> str;
	str.insert("123");
	str.insert("24");
	unorderset<string>::iterator it = str.begin();
	while (it != str.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
int main()
{
	//test();
	test1();
	system("pause");
	return 0;
}