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
    Tool *tl  = new Tool(argv[2],argv[4],argv[6],argv[7]);    
    //1、开启线程
    tl->StartSvr();
    //int a = tl->GetTimeDifference();
    //printf("%d\n",a);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
