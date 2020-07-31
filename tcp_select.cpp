/*************************************************************************
    > File Name: main.cpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年07月31日 星期五 15时45分27秒
 ************************************************************************/

#include "SelectSvr.hpp"
#define CHECK_RET(p) if(p == false){return -1;}
int main()
{
    Tcpsvr ts1;
    CHECK_RET(ts1.Createsocket());
    CHECK_RET(ts1.Bind("0.0.0.0",19999));
    CHECK_RET(ts1.Listen());
    SelectSvr ss;
    ss.Addfd(ts1.Getfd());
    while(1)
    {
        std::vector<Tcpsvr> vec;
        if(!ss.selectwait(&vec))
        {
            continue;
        }
        for(size_t i = 0 ; i < vec.size(); i++)
        {
            if(vec[i].Getfd() == ts1.Getfd())
            {
                //是侦听套接字
                Tcpsvr news;
                struct sockaddr_in peeraddr;
                //获取新的连接
                ts1.Accept(&news,&peeraddr);
                printf("Have a new conntion [ip]:%s [port]:%d\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
                ss.Addfd(news.Getfd());
            }
            else
            {
                //是新连接的套接字
                std::string buf;
                bool ret = vec[i].Recv(&buf);
                if(!ret)
                {
                    //1、把该套接字描述符从事件集合中删除
                    //2、关闭连接
                    ss.Deletefd(vec[i].Getfd());
                    vec[i].Close();
                }
                printf("recv a data from client : [%s]\n",buf.c_str());
                std::string message;
                fflush(stdout);
                printf("请输入你想说的话：");
                std::cin >> message;
                vec[i].Send(message);
            }
        }
    }
    return 0;
}

