#include<iostream>
#include<map>
#include<set>
using namespace std;
void test()
{
	set<int> str;
	str.insert(1);
	str.insert(2);
	str.insert(4);
	str.insert(3);
	str.insert(3);
	set<int>::iterator it = str.begin();
	while (it != str.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
void test2()
{
	map<int,int> str;
	str.insert(pair<int, int>(1, 2));
	str.insert(make_pair(2, 3));
	str[3] = 3;
	str[4] = 4;
	str.at(5) = 100;
	map<int, int>::iterator it = str.begin();
	while (it != str.end())
	{
		cout << it->first << "----->" << it->second << endl;
		it++;
	}
}
int main()
{
	//test();
	test2();
	system("pause");
	return 0;
}