/*************************************************************************
    > File Name: test.c
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年08月14日 星期五 20时58分47秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int test()
{
    int a = 2;
    int b = 10;
    int *p = (int*)malloc(sizeof(int));
    free(p);
    return a + b;
}
int main()
{
    int z = test();
    printf("z = %d\n",z);
    return 0;
}

