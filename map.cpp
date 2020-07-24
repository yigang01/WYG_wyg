#include<iostream>
using namespace std;
#include<vector>
#include<string>
class BitMap
{
public:
	BitMap(size_t n)
	{
		_bit.resize(n / 32 + 1);
	}
	bool Test(size_t n)//查找
	{
		int idx = n / 32;//先找到整数位置
		int bitidx = n % 32;//在找到具体的比特位置
		if ((_bit[idx] >> bitidx) & 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Set(size_t n)//设置，即插入
	{
		int idx = n / 32;
		int bitidx = n % 32;
		_bit[idx] = _bit[idx] | (1 << bitidx);
	}
	void Reset(size_t n)//删除
	{
		int idx = n / 32;
		int bitidx = n % 32;
		_bit[idx] = _bit[idx] & ~(1 << bitidx);
	}
private:
	vector<int> _bit;
};
void test()
{
	BitMap bt(100);
	bt.Set(30);
	bt.Reset(30);
	cout << bt.Test(30) << endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}