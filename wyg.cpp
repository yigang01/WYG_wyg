/*************************************************************************
    > File Name: wyg.cpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年10月02日 星期五 23时42分55秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <chrono>
#include "http.hpp"
#include "socket.hpp"
#include "select.hpp"
void *socket_start(void *arg)
{
    Socket *st = (Socket *)arg; 
    Select ss;
    Http ht(st->url);
    pthread_mutex_lock(&(st->_mutex));
    int count = st->_count;//每个线程的请求数
    st->host = ht.host;
    //1、创建套接字
    st->CreateSocket();
    //2、发起连接
    bool ret1 = st->Connect(ht.host,ht.port);
    //3、将socket设置为非阻塞
    st->setsocket();
    //4、将该套接字描述符添加到事件集合中
    ss.Addfd(st->_sockfd);
    //5、循环的去发送数据
    while(count > 0)
    {
        bool ret2 = st->Send(ht.http());//发送数据给服务端
        if(ret1 == true && ret2 == true)
        {
            st->sucessed ++;
        }
        std::string buf;
        //st->Recv(&buf);
        //printf("%s\n",buf.c_str());
        count--;
        usleep(st->_time);//等待时间发送
    }
    //5、select进行监控
    std::vector<Socket> vec;
    ss.selectwait(&vec);//进行监控
    std::string buf;
    for(size_t i = 0; i < vec.size();i++)
    {
        bool ret = vec[i].Recv(&buf);
        if(!ret)
        {
            ss.Deletefd(st->_sockfd);
            vec[i].Close();
        }
    }
    //6、关闭套接字
    st->Close();
    pthread_mutex_unlock(&(st->_mutex));
    return NULL;
}
int main(int argc,char *argv[])
{

    struct timeval start, end;
    //1、获取给定的参数中的值
    char *pthread = argv[2]; //从环境变量中获取输入的线程数
    char *connect = argv[4]; //从环境变量中获取输入的总连接数
    char *simultaneously = argv[6]; //从环境变量中获取输入的并发数
    std::string url = argv[7]; //从环境变量中获取输入的域名
    //2、讲获取的值转化为整数形式
    int PTHREADCOUNT = atoi(pthread); //线程数
    int clients = atoi(connect); //总连接数
    int same = atoi(simultaneously); //并发数
    //3、计算出每个线程需要发送请求个数
    int num = clients / PTHREADCOUNT;//每个线程发送的请求个数
    //4、计算出每个请求之间相隔时间
    double sumtime = (double)(  clients / same);//发完总连接数个请求需要多少秒
    double singletime = ((double)(sumtime / clients)) * 1000000;//每个请求之间相隔多少秒发送下一个请求（单位微秒）
    Socket *st = new Socket(num,singletime,url);
    //5、创建线程
    int i = 0;
    gettimeofday( &start, NULL  );//开始计时
    pthread_t tid[PTHREADCOUNT]; 
    for(i = 0;i < PTHREADCOUNT;i++)
    {
        int ret = pthread_create(&tid[i],NULL,socket_start,(void *)st);
        if(ret < 0)
        {
            perror("pthread_create");
            return -1;
        }
    }
    for(i = 0;i < PTHREADCOUNT;i++)
    {
        pthread_join(tid[i],NULL);
    }
    gettimeofday( &end, NULL);//结束计时
    delete st;
    //6、计算结果
    int timeuse = 1000000 *( end.tv_sec - start.tv_sec  ) + end.tv_usec -start.tv_usec;
    int _time = timeuse / 1000000;
    printf("请求总时长：%d 微秒\n",timeuse);
    printf("解析后的ip地址为：%s\n",(st->host).c_str());
    printf("每秒发送的http请求：%d\n",(int)(st->sucessed / _time));
    printf("请求成功：%d\n",st->sucessed);
    printf("请求失败：%d\n",clients - st->sucessed);
    return 0;
}
