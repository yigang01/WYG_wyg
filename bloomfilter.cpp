#include<iostream>
#include<vector>
using namespace std;
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
template <class T,class HF1,class HF2,class HF3>
class Bloomfliter
{
public:
	Bloomfliter(size_t num)
		:_bit(5 * num)
		, _bitcount(5 * num)
	{}
	void Set(const T& val)//设置一个值
	{
		HF1 hf1;
		HF2 hf2;
		HF3 hf3;
		size_t hashcode1 = hf1(value);
		size_t hashcode2 = hf2(value);
		size_t hashcode3 = hf3(value);

		_bit.Set(hashcode1 % _bitcount);
		_bit.Set(hahscode2 % _bitcount);
		_bit.Set(hashcode3 % _bitcount);
	}
	bool Test(const T& value)
	{
		HF1 hf1;
		size_t hashcode1 = hf1(value);
		if (!_bit.Test(hashcode1 % _bitcount))
		{
			return false;
		}
		HF2 hf2;
		size_t hashcode2 = hf2(value);
		if (!_bit.Test(hashcode2 % _bitcount))
		{
			return false;
		}
		HF3 hf3;
		size_t hashcode3 = hf3(value);
		if (!_bit.Test(hashcode3 % _bitcount))
		{
			return false;
		}
		return true;
	}
private:
	BitMap _bit;
	size_t _bitcount;
};
struct strToInt1
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

struct strToInt2
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto& ch : str)
		{
			hash = hash * 65599 + ch;
		}
		return hash;
	}
};

struct strToInt3
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		size_t magic = 63689;
		for (auto& ch : str)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};
int main()
{
	system("pause");
	return 0;
}
