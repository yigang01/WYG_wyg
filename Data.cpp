#include<iostream>
using namespace std;
class Date
{
public:
	void print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
	int Getmonthday(int year, int month)//获取某一年某个月有多少天
	{
		static int array[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = array[month];
		if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		{
			day += 1;
		}
		return day;
	}
	Date(int year = 1, int month = 1, int day = 1)//全缺省构造函数
	{
		if ((year <= 0) || (month < 1 && month>12) || (day > Getmonthday(year, month)))
		{
			cout << "你输入的月份和天数不符合实际情况" << endl;
			_year = _month = _day = 1;
			cout << "已重置为" << " " << "_year = " << _year << " " << "_month = ",
				cout << _month << " " << "_day = " << _day << endl;
		}
		else
		{
			_year = year;
			_month = month;
			_day = day;
		}
	}
	Date(const Date& date)//拷贝构造
	{
		_year = date._year;
		_month = date._month;
		_day = date._day;
	}
	//~Date();//析构函数
	Date& operator=(const Date& date)//赋值运算符
	{
		_year = date._year;
		_month = date._month;
		_day = date._day;
	}
	Date& operator+=(int day)//加等运算符  日期+天数
	{
		if (day < 0)
		{
			return *this -= -day;
		}
		_day += day;
		while (_day > Getmonthday(_year, _month))
		{
			_day = _day - Getmonthday(_year, _month);
			_month += 1;
			if (_month == 13)
			{
				_year += 1;
			}
		}
		return *this;
	}
	Date& operator-=(int day)//减等运算符  日期-天数
	{
		if (day < 0)
		{
			return *this += -day;
		}
		_day -= day;
		while (_day <= 0)
		{
			_month--;
			if (_month == 0)
			{
				_year--;
			}
			_day += Getmonthday(_year, _month);
		}
		return *this;
	}
	Date operator+(int day)//加法运算符 加一个天数
	{
		Date ret = *this;
		return ret += day;
	}
	Date operator-(int day)//减法运算符 减一个天数
	{
		Date ret = (*this);
		return ret -= day;
	}
	Date &operator++()//前置++运算符
	{
		return *this += 1;
	}
	Date operator++(int)//后置++运算符
	{
		Date ret = (*this);
		return ret += 1;
	}
	Date& operator--()//前置--运算符
	{
		return *this -= 1;
	}
	Date operator--(int)//后置--运算符
	{
		Date ret = (*this);
		return ret -= 1;
	}
	bool operator>(const Date& d)//大于运算符
	{
		if (_year > d._year)
		{
			return true;
		}
		else if (_year == d._year)
		{
			if (_month > d._month)
			{
				return true;
			}
			else if (_month == d._month)
			{
				if (_day > d._day)
				{
					return true;
				}
			}
		}
		return false;
	}
	bool operator<(const Date& d)//小于运算符
	{
		return !(*this >= d);
	}
	bool operator==(const Date& d)//等于运算符
	{
		if (_year == d._year && _month == d._month && _day == d._day)
		{
			return true;
		}
		return false;
	}
	bool operator>=(const Date& d)//大于等于运算符
	{
		return *this > d || *this == d;
	}
	bool operator<=(const Date& d)//小于等于运算符
	{
		return !(*this > d);
	}
	bool operator!=(const Date& d)//不等于运算符
	{
		return !(*this == d);
	}
	int operator-(const Date& d)//日期-日期  返回天数
	{
		int day = 0;
		if (*this > d)
		{
			Date ret = d;
			while (ret != *this)
			{
				++ret;
				day++;
			}
		}
		else if (*this < d)
		{
			Date ret = (*this);
			while (ret != d)
			{
				++ret;
				day++;
			}
		}
		else
		{
			day = 0;
		}
		return day;
	}
private:
	int _year;
	int _month;
	int _day;
};
void test()
{
	Date d1(2021, 8, 18);
	Date d2(2020, 8, 18);
	cout << d1 - d2 << endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}