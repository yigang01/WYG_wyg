#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
void Reverse(char *start, char *end)
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
void Left_Move(char *a, int len, int k)
{
	int step = k%len;
	Reverse(a, a + step - 1);
	Reverse(a + step, a + len - 1);
	Reverse(a, a + len - 1);
	printf("%s", a);
}
int main()
{
	char a[] = "ABCD";
	int k = 0;
	scanf("%d", &k);
	Left_Move(a, strlen(a), k);
	system("pause");
	return 0;
}