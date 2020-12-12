/************************************************************************
    > File Name: tcp_svr.h
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年06月23日 星期二 11时55分19秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

class Tcpsvr
{
    public:
        Tcpsvr()
        {
            _sockfd = -1;
        }
        ~Tcpsvr()
        {}
        bool Createsocket()//创建套接字
        {
            _sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(_sockfd < 0)
            {
                perror("socket");
                return false;
            }
            return true;
        }
        bool Bind(const std::string& ip,uint16_t port)//绑定地址信息
        {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            int ret = bind(_sockfd,(struct sockaddr*)&addr,sizeof(addr));
            if(ret < 0)
            {
                perror("bind");
                return false;
            }
            return true;
        }
        bool Listen(int backlog = 5)//监听
        {
            int ret = listen(_sockfd,backlog);
            if(ret < 0)
            {
                perror("listen");
                return false;
            }
            return true;
        }
        bool Accept(Tcpsvr *newts,struct sockaddr_in* peeraddr)//获取连接
        {
            socklen_t addrlen = sizeof(struct sockaddr_in);
            int newfd = accept(_sockfd,(struct sockaddr*)peeraddr,&addrlen);
            if(newfd < 0)
            {
                perror("accept");
                return false;
            }
            newts->_sockfd = newfd;
            return true;
        }
        bool Connect(const std::string& ip,uint16_t port)//发起连接
        {
            struct sockaddr_in dest_addr;
            dest_addr.sin_family = AF_INET;
            dest_addr.sin_port = htons(port);
            dest_addr.sin_addr.s_addr = inet_addr(ip.c_str());
            int ret = connect(_sockfd,(struct sockaddr*)&dest_addr,sizeof(dest_addr));
            if(ret < 0)
            {
                perror("connect");
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
        int GetFd()//获取套接字描述符
        {
            return _sockfd;
        }
        void Close()//关闭套接字
        {
            close(_sockfd);
        }
    private:
        int _sockfd;
};
