/************************************************************************
    > File Name: test.hpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年10月16日 星期五 14时21分23秒
 ************************************************************************/

#pragma once
#include<iostream>
typedef struct processes //进程里面的信息
{
    int t_gid_;//进程id
    std::string status_;//进程状态
    int priority_;//进程优先级队列
    struct processes *next_;//下一个节点
}processes;
class process
{
    public:
        process()
        {
            Run_head = new processes;
            Run_end = new processes;
            Wait_head = new processes;
            Wait_end = new processes;
            block_head = new processes;
            block_end = new processes;
            Node = new processes;
        }
        ~process()
        {
            delete Run_head;
            delete Run_end;
            delete Wait_head;
            delete Wait_end;
            delete block_head;
            delete block_end;
            delete Node;
        }
        void InPutRun(std::string& _status,int pid,int pro)//在就绪链表插入一个节点
        {
            Node->status_ = _status;
            Node->t_gid_ = pid;
            Node->priority_ = pro;
            Run_head->next_ = Run_end->next_ = Node;
            Run_end = Run_end->next_;//尾节点更新一下
            std::cout << "插入成功！！！"<<std::endl;
        }
        void InPutWait(std::string& _status,int pid,int pro)//在等待链表插入一个节点
        {
            Node->status_ = _status;
            Node->t_gid_ = pid;
            Node->priority_ = pro;
            Wait_head->next_ = Wait_end->next_ = Node;
            Wait_end = Wait_end->next_;//尾节点更新一下
            std::cout << "插入成功！！！"<<std::endl;
        }
        void InPutBlock(std::string& _status,int pid,int pro)//在阻塞链表插入一个节点
        {
            Node->status_ = _status;
            Node->t_gid_ = pid;
            Node->priority_ = pro;
            block_head->next_ = block_end->next_ = Node;
            block_end = block_end->next_;//尾节点更新一下
            std::cout << "插入成功！！！"<<std::endl;
        }
        void PrintRun()//打印就绪链表
        {
            std::cout << "就绪链表信息如下：";
            struct processes* cur = Run_head;
            while(cur)
            {
                std::cout << cur->status_<< " ";
                cur = cur->next_;
            }
            std::cout << std::endl;
        }
        void PrintWait()//打印等待链表
        {
            std::cout << "等待链表信息如下：";
            struct processes* cur = Wait_head;
            while(cur)
            {
                std::cout << cur->status_<< " ";
                cur = cur->next_;
            }
            std::cout << std::endl;
        }
        void PrintBlock()//打印阻塞链表
        {
            std::cout << "阻塞链表信息如下：";
            struct processes* cur = block_head;
            while(cur)
            {
                std::cout << cur->status_<< " ";
                cur = cur->next_;
            }
            std::cout << std::endl;
        }
    private:
        struct processes* Run_head;//就绪头指针
        struct processes* Run_end;//就绪尾指针
        struct processes* Wait_head;//等待头指针
        struct processes* Wait_end;//等待头指针
        struct processes* block_head;//阻塞头指针
        struct processes* block_end;//阻塞头指针
        struct processes* Node;
};

