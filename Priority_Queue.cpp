#include<iostream>
#include<queue>
#include<vector>
#include<list>
#include<functional>
using namespace std;
template<class T,class Container  = vector<T>,class Compare = less<T>>
class Priority_Queue
{
public:
	void push(const T& val)//入堆
	{
		_c.push_back(val);
		shiftup(_c.size() - 1);
	}
	void pop()//出堆
	{
		swap(_c[0], _c[_c.size() - 1]);
		_c.pop_back();
		shiftdown(0);
	}
	const T& top()//获取堆顶元素
	{
		return _c.front();
	}
	size_t size()//获取当前堆（优先队列）有效元素个数
	{
		return _c.size();
	}
	bool empty()//判断堆是否为空
	{
		return _c.empty();
	}
private:
	void shiftdown(int parent)//向下调整
	{
		int child = 2 * parent + 1;
		while (child < _c.size())
		{
			if (child + 1 < _c.size() && _com(_c[child + 1],_c[child]))
			{
				child += 1;
			}
			if (_com(_c[parent],_c[child]))
			{
				swap(_c[parent], _c[child]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
			{
				break;
			}
		}
	}
	void shiftup(int child)//向上调整
	{
		int parent = (child - 1) / 2;
		while (child > 0)
		{
			if (_com(_c[parent],_c[child]))
			{
				swap(_c[parent], _c[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
private:
	Container _c;
	Compare _com;
};
void test1()//按大堆排列
{
	Priority_Queue<int> str;//默认按照大堆排列
	str.push(1);
	str.push(23);
	str.push(9);
	str.push(27);
	str.push(45);
	str.push(19);
	while (!str.empty())
	{
		cout << str.top() << " ";
		str.pop();
	}
	cout << endl;
}
void test2()//按小堆排列
{
	Priority_Queue<int,vector<int>,greater<int>> str;
	str.push(1);
	str.push(23);
	str.push(9);
	str.push(27);
	str.push(45);
	str.push(19);
	while (!str.empty())
	{
		cout << str.top() << " ";
		str.pop();
	}
	cout << endl;
}
int main()
{
	test1();
	test2();
	system("pause");
	return 0;
}