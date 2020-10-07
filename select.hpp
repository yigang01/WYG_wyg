/*************************************************************************
    > File Name: select.hpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年10月02日 星期五 03时14分31秒
    > 描述：多路转接select模型，添加删除socket描述符到事件集合中去，进行监控
 ************************************************************************/
#pragma once
#include<stdio.h>
#include<unistd.h>
#include<sys/select.h>
#include<vector>
#include "socket.hpp"

class Select
{
    public:
        Select()
        {
            _maxfd = -1;
            FD_ZERO(&_readfd);
        }
        ~Select()
        {}
        void Addfd(int fd)//添加文件描述符到事件集合中去
        {
            //1、添加
            FD_SET(fd,&_readfd);
            //2、更新_maxfd（监控的最大文件描述符）
            if(fd > _maxfd)
            {
                _maxfd = fd;
            }
        }
        void Deletefd(int fd)//从事件集合中移除该文件描述符
        {
            FD_CLR(fd,&_readfd);
            int i = 0;
            for(i = _maxfd;i >= 0; i--)
            {
               if(FD_ISSET(i,&_readfd) == 0)
               {
                    continue;
               }
               _maxfd = i;
               break;
            }
        }
        bool selectwait(std::vector<Socket>* vec)
        {
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 0;
            fd_set tmp = _readfd;
            int ret = select(_maxfd + 1,&tmp,NULL,NULL,&tv);
            if(ret < 0)
            {
                return false;
            }
            else if(ret == 0)
            {
                //printf("select timeout\n");
                return false;
            }
            int i = 0;
            for(i = 0; i <= _maxfd; i++)
            {
                if(FD_ISSET(i,&tmp))
                {
                   Socket st1;
                   st1.Setfd(i);
                   vec->push_back(st1); 
                }
            }
            return true;
        }
    private:
        int _maxfd;
        fd_set _readfd;
};
