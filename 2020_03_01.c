#include<stdio.h>
#include<windows.h>
#pragma warning(disable:4996)
int main()
{
	printf("Please Enter src path:\n");
	char src_path[1024];
	scanf("%s", &src_path);
	printf("Please Enter dst path:\n");
	char dst_path[1024];
	scanf("%s", dst_path);
	FILE *src_p = fopen(src_path, "rb");
	FILE *dst_p = fopen(dst_path, "wb");
	if (src_p == NULL || dst_p == NULL)
	{
		printf("fopen file error!\n");
		return 1;
	}
	fseek(src_path, 0, SEEK_END);
	long int size = ftell(src_path);
	char *temp = (char *)malloc(size*sizeof(char));
	while (temp)
	{
		fread(temp, size, 1, src_p);
		fwrite(temp, size, 1, dst_p);
	}
	fclose(src_p);
	fclose(dst_p);
	free(temp);
	system("pause");
	return 0;
}