/*************************************************************************
    > File Name: wyg.cpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年10月02日 星期五 23时42分55秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h>
#include "main.hpp"
int main(int argc,char *argv[])
{
    HttpLoad *tl  = new HttpLoad();
    if(!tl)
    {
        printf("create HttpLoad failed\n");
        return -1;
    }

    tl->InitSvr(argc, argv);
    //1、开启线程
    tl->StartSvr();
    //2、打印结果
    tl->result();
    return 0;
}
