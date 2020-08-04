#include<iostream>
union a1
{
	int a;
	char b;
};
int main()
{
	//第一种方法
	a1 q;
	q.a = 1;
	if (q.b == 1)
	{
		std::cout << "小端" << std::endl;
	}
	else
	{
		std::cout << "大端" << std::endl;
	}
	//第二种方法
	int a = 1;
	char *b = (char*)&a;
	if (*b == 1)
	{
		std::cout << "小端" << std::endl;
	}
	else
	{
		std::cout << "大端" << std::endl;
	}
	system("pause");
	return 0;
}
