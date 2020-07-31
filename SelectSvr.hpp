#pragma once
#include<stdio.h>
#include<unistd.h>
#include<sys/select.h>
#include<vector>
#include "tcp_svr.hpp"

class SelectSvr
{
    public:
        SelectSvr()
        {
            _maxfd = -1;
            FD_ZERO(&_readfd);
        }
        ~SelectSvr()
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
        bool selectwait(std::vector<Tcpsvr>* vec)
        {
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 3000;
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
                   Tcpsvr ts2;
                   ts2.setfd(i);
                   vec->push_back(ts2); 
                }
            }
            return true;
        }
    private:
        int _maxfd;
        fd_set _readfd;
};
