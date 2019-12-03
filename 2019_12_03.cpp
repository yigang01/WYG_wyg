#include<stdio.h>
#include<windows.h>
#include<assert.h>
#pragma warning(disable:4996)
int Mystrcat(char *a, char *b)
{
	assert(a != NULL);
	assert(b != NULL);
	char *dp = a;
	while (*dp != NULL)
	{
		dp++;
	}
	while (*b != NULL)
	{
		*dp++ = *b++;
	}
	return *a;
}
int main()
{
	char a[16] = "I love";
	char b[16] = "you";
	Mystrcat(a, b);
	printf("%s", a);
	system("pause");
	return 0;
}