#include<iostream>
#include<vector>
using namespace std;
enum State
{
	EMPTY,
	EXIST,
	DELETE
};
template<class K, class V>
struct hashNode
{
	pair<K, V> _val;
	State _state;
	hashNode(const pair<K, V>& value = pair<K, V>())
		:_state(EMPTY)
		, _val(value)
	{}
};
template<class K,class V>
class hashTable
{
public:
	hashTable(int n = 10)
	{
		_table.resize(n);
		_size = 0;
	}
	bool insert(const pair<K,V>& value)//插入操作
	{
		//1、检查容量
		checkcapacity();
		//2、计算哈希位置，即要插入的数据应该放入的位置
		int idx = value.first % _table.size();
		//3、判断位置是否可用和数据是否已经存在
		while (_table[idx]._state == EXIST)
		{
			if (_table[idx]._val.first == value.first)
			{
				return false;
			}
			idx++;
			if (idx == _table.size())
			{
				idx = 0;
			}
		}
		//一定找到了一个空的位置或者已经删除了的位置
		_table[idx]._val = value;
		_table[idx]._state = EXIST;
		_size++;
		return true;
	}
	void checkcapacity()
	{
		if (_size * 10 / _table.size() >= 7)//负载因子大于等于百分之70的时候就需要进行扩容了
		{
			hashTable ht(2 * _table.size());
			//把旧表中元素插入到新表中去
			int i = 0;
			for (i = 0; i < _table.size(); i++)
			{
				if (_table[i]._state == EXIST)
				{
					ht.insert(_table[i]._val);
				}
			}
			swap(_table, ht._table);
		}
	}
	hashNode<K, V> *find(const K& key)//查找
	{
		int idx = key % _table.size();
		//遇到空结束查找
		while (_table[idx]._state != EMPTY)
		{
			if (_table[idx]._state == EXIST && _table[idx]._val.first == key)
			{
				return &_table[idx];
			}
			idx++;
			if (idx == _table.size())
			{
				idx = 0;
			}
		}
		return nullptr;
	}
	bool erase(const K& key)//删除
	{
		hashTable<K, V> *ptr = find(key);
		if (ptr)
		{
			ptr->_state == DELETE;
			_size--;
			return true;
		}
		return false;
	}
private:
	vector<hashNode<K, V>> _table;
	size_t _size;
};
void test()
{
	hashTable<int, int> str;
	str.insert(make_pair(1, 2));
	str.insert(make_pair(2, 3));
}
int main()
{
	test();
	system("pause");
	return 0;
}
