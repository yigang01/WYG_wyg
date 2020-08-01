#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<vector>
#include<sys/epoll.h>
#include"tcp_svr.hpp"
class EpollSvr
{
    public:
        EpollSvr()
        {
            _epollfd = -1;
        }
        ~EpollSvr()
        {}
        bool InitSvr()
        {

            _epollfd = epoll_create(10);
            if(_epollfd < 0)
            {
                perror("epoll_create");
                return false;
            }
            return true;
        }
        bool Addfd(int fd)
        {
            struct epoll_event et;
            et.events = EPOLLIN;
            et.data.fd = fd;
            int ret = epoll_ctl(_epollfd,EPOLL_CTL_ADD,fd,&et);
            if(ret < 0)
            {
                perror("epoll_ctl");
                return false;
            }
            return true;
        }
        bool Deletefd(int fd)
        {
            int ret = epoll_ctl(_epollfd,EPOLL_CTL_DEL,fd,NULL);
            if(ret < 0)
            {
                perror("epoll_ctl");
                return false;
            }
            return true;
        }
        bool epollwait(std::vector<Tcpsvr> *out)
        {
            struct epoll_event fd_arr[10];
            int ret = epoll_wait(_epollfd,fd_arr,sizeof(fd_arr)/sizeof(fd_arr[0]),-1);
            if(ret < 0)
            {
                return false;
            }
            else if(ret == 0)
            {
                //只有带有超时时间的时候，才会返回这个
                return false;
            }
            else
            {
                //ret返回的是文件描述符的个数
                if(ret > sizeof(fd_arr)/sizeof(fd_arr[0]))
                {
                    ret = sizeof(fd_arr)/sizeof(fd_arr[0]);
                }
                for(int i = 0; i < ret;i++)
                {
                    Tcpsvr ts;
                    ts.setfd(fd_arr[i].data.fd);
                    out->push_back(ts);
                }
            }
            return true;
        }
    private:
        int _epollfd;
};
