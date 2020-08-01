/*************************************************************************
    > File Name: tcp_epoll.cpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年07月31日 星期五 18时09分30秒
 ************************************************************************/

#include"EpollSvr.hpp"
#define CHECK_RET(p) if(p == false){return -1;}
int main()
{
    Tcpsvr ts;
    CHECK_RET(ts.Createsocket());
    CHECK_RET(ts.Bind("0.0.0.0",19999));
    CHECK_RET(ts.Listen());
    EpollSvr es;
    CHECK_RET(es.InitSvr());
    es.Addfd(ts.Getfd());
    while(1)
    {
        //监控
        std::vector<Tcpsvr> vec;
        if(!es.epollwait(&vec))
        {
            continue;
        }
        for(size_t i = 0;i < vec.size();i++)
        {
            //判断是否是侦听套接字
            if(vec[i].Getfd() == ts.Getfd())
            {
                //是侦听套接字
                Tcpsvr news;
                struct sockaddr_in peeraddr;
                ts.Accept(&news,&peeraddr);
                //将该侦听套接字描述符添加到事件集合中去
                es.Addfd(news.Getfd());
                printf("Have a new conntion：[%s] [%d]\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
            }
            else
            {
                std::string buf;
                bool ret = vec[i].Recv(&buf);
                if(!ret)
                {
                    es.Deletefd(vec[i].Getfd());
                    vec[i].Close();
                }
                printf("Have a data from client: [%s]\n",buf.c_str());

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
