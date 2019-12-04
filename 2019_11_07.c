#include<stdio.h>
#include<assert.h>
#include<windows.h>
int Mystrcat(char *a, char *b)
{
	assert(a != NULL);
	assert(b != NULL);
	char *dp = a;
	while (*dp != '\0')
	{
		dp++;
	}
	while (*b != '\0')
	{
		*dp++ = *b++;
	}
	return *a;
}
int main()
{
	char a[16] = "I love ";
	char b[16] = "you";
	Mystrcat(a, b);
	printf("%s", a);
	system("pause");
	return 0;
}