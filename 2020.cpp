#include<stdio.h>
#include<windows.h>
#include<math.h>
#pragma warning(disable:4996)
void Revese(char *start, char *end)
{
	while (start < end)
	{
		*start ^= *end;
		*end ^= *start;
		*start ^= *end;
		start++;
		end--;
	}
}
void Move(char *str, int num, int k)
{
	int temp = k%num;
	Revese(str, str + temp - 1);
	Revese(str + temp, str + num - 1);
	Revese(str, str + num - 1);
	printf("%s", str);
}
int main()
{
	char str[] = "ABCD";
	int k = 0;
	scanf("%d", &k);
	Move(str, strlen(str), k);
	system("pause");
	return 0;
}