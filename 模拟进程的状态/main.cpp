/*************************************************************************
    > File Name: main.c
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年10月16日 星期五 14时49分45秒
 ************************************************************************/

#include <iostream>
#include "test.hpp"
int main()
{
    process *ps = new process;
    while(1)
    {
        std::string status_; 
        int pid;
        int pro;
        std::cout << "请输入你想输入的进程的状态："<<std::endl;
        std::cin >> status_;
        std::cout << "请输入你想输入的进程的进程号："<<std::endl;
        std::cin >> pid;
        std::cout << "请输入你想输入的进程的优先级队列："<<std::endl;
        std::cin >> pro;
        if(status_ == "Running")
        {
            ps->InPutRun (status_,pid,pro);
        }
        else if(status_ == "Waitting")
        {
            ps->InPutWait(status_,pid,pro);
        }
        else if(status_ == "Block")
        {
            ps->InPutBlock(status_,pid,pro);
        }
        else
        {
            std::cout << "输入有误，请重新输入"<< std::endl;
        }
    }
    return 0;
}
