/*************************************************************************
    > File Name: socket.hpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年09月30日 星期三 11时45分24秒
    > 描述：socket编程
 ************************************************************************/

#pragma once
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

class Socket
{
    public:
        Socket()
        {

        }
        Socket(int num,int singletime,const std::string& _url)
        {
            _sockfd = 0;
            _count = num;
            url = _url;
            _time = singletime;
            sucessed = 0;
            failed = 0;
            pthread_mutex_init(&_mutex,NULL);
        }
        ~Socket()
        {
            pthread_mutex_destroy(&_mutex);
        }
        bool CreateSocket()//创建套接字
        {
            _sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(_sockfd < 0)
            {
                perror("socket");
                return false;
            }
            return true;
        }
        bool Connect(const std::string& ip,uint16_t port)//发起连接，传入的是服务端的ip和端口
        {
            struct sockaddr_in svr_addr;
            svr_addr.sin_addr.s_addr = inet_addr(ip.c_str());
            svr_addr.sin_family = AF_INET;
            svr_addr.sin_port = htons(port);
            int ret = connect(_sockfd,(struct sockaddr*)&svr_addr,sizeof(svr_addr));
            if(ret < 0)
            {
                perror("connect");
                return false;
            }
            return true;
        }
        bool Send(const std::string &data)//发送数据
        {
            int send_size = send(_sockfd,data.c_str(),data.size(),MSG_DONTWAIT);
            if(send_size < 0)
            {
                perror("send");
                return false;
            }
            return true;
        }
        bool Recv(std::string* data)//接收数据
        {
            char buf[1024] = {0};
            int recv_size = recv(_sockfd,buf,sizeof(buf) - 1,0);
            if(recv_size < 0)
            {
                perror("recv");
                return false;
            }
            else if(recv_size == 0)
            {
                //对端关闭了连接
                printf("peer shutdown connect\n");
                return false;                             
            }
            data->assign(buf,recv_size);
            return true;
        }
        bool setsocket()//设置socket为非阻塞发送
        {
            int flag = fcntl(_sockfd,F_GETFL);
            int ret = fcntl(_sockfd, F_SETFL, flag | O_NONBLOCK);
            if(ret < 0)
            {
                perror("fcntl");
                return false;
            }
            return true;
        }
        int Getfd()//获取套接字描述符
        {
            return _sockfd;
        }
        void Setfd(int fd)//设置套接字描述符
        {
            _sockfd = fd;
        }
        void Close()//关闭套接字
        {
            close(_sockfd);
        }
        void seturl(std::string& _url)
        {
            url = _url; 
        }
    public:
        int _sockfd;
        pthread_mutex_t _mutex;
        int _count;//每个线程请求的个数
        int _time;//每个请求之间相隔的时间
        std::string url;
        int sucessed;//成功数
        int failed;//失败数
        std::string host;//解析后的ip地址
};

