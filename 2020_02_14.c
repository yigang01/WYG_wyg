#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
union endian
{
	int i;
	char a;
}en;
int main()
{
	en.i = 1;
	if (en.a == 1)
	{
		printf("Ð¡¶Ë\n");
	}
	else
	{
		printf("´ó¶Ë\n");
	}
	system("pause");
	return 0;
}