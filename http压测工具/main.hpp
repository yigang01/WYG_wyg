/*************************************************************************
    > File Name: main.cpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年10月09日 星期五 10时58分28秒
 ************************************************************************/

#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <time.h>
#include <sys/time.h>
#include "socket.hpp"
#include "select.hpp"
#include "http.hpp"

//线程属性类
typedef struct time_select
{
    int _time_sum;//线程运行时间
    pthread_t thread_tid;//线程标识符
    Tool *tl;
    //struct timeval _start, _end;//计时
}time_select;

class Tool
{
    public:
        Tool(char *pthread,char* connect,char *simultaneously,std::string url)
        {
            _pthread = atoi(pthread);
            _connect = atoi(connect);
            _simultaneously = atoi(simultaneously);
            _url = url;
            _num = _connect / _pthread;
            double sumtime = (double)(  _connect / _simultaneously);//发完总连接数个请求需要多少秒
            _singletime = ((double)(sumtime / _connect)) * 1000000;
            st = new Socket(_url);
            hp = new Http(_url);
            ss = new Select();
        }
        ~Tool()
        {
            delete st;
            delete hp;
            delete ss;
        }

	    //开启线程
	    int StartSvr()
	    {
	        pthread_t tid[_pthread];	
            time_select *tt = new time_select();
            for(int i = 0; i < _pthread;i++)
            {
                tt->thread_tid = tid[i];//获取到了当前线程的标识符
                int ret = pthread_create(&tid[i],NULL,ThreadStart,(void*)tt);
                printf("创建线程后返回值为：%d\n",ret);
                if(ret < 0)
                {
                    perror("pthread_create");
                    return -1;
                }
            }
            return 1;
	    }

	    //线程入口函数
	    static void* ThreadStart(void* arg)
	    {
            printf("开始进入线程入口函数:\n");
            time_select *ts = (time_select*)arg;
            //开始计时
            //gettimeofday(&(ts->_start),NULL);
            //ts->tl->start_time();
            //1、创建套接字
            ts->tl->st->CreateSocket();
            //2、发起连接
            bool ret1 = ts->tl->st->Connect(ts->tl->hp->host,ts->tl->hp->port);
            //3、设置socket为非阻塞
            ts->tl->st->setsocket();
            //4、添加该线程的套接字描述符到select中
            ts->tl->ss->Addfd(ts->tl->st->_sockfd);
            //5、发送数据
            while(ts->tl->_num)
            {
                bool ret2 = ts->tl->st->Send(ts->tl->hp->http());
                std::string buf;
                ts->tl->st->Recv(&buf);
                printf("%s\n",buf.c_str());
                if(ret1 == true && ret2 == true)
                {
                    ts->tl->st->sucessed ++;//连接和发送数据都成功了
                }
                usleep(ts->tl->_singletime);//间隔时间
                ts->tl->_num --;
            }

            //6、select进行监控
            std::vector<Socket> vec;
            ts->tl->ss->selectwait(&vec);//进行监控
            for(size_t i = 0 ; i < vec.size(); i++)
            {
                std::string buf;
                bool ret = vec[i].Recv(&buf);
                if(!ret)
                {
                    ts->tl->ss->Deletefd(vec[i].Getfd());
                    vec[i].Close();            
                }         
            }
            //5、关闭套接字
            ts->tl->st->Close();
            //结束计时
            //ts->tl->end_time();
            //gettimeofday(&(ts->_end),NULL);
            //int timeuse = 1000000 *( ts->_end.tv_sec - ts->_start.tv_sec) + ts->_end.tv_usec -ts->_start.tv_usec;
            //ts->_time_sum = timeuse;
            ts->tl->thread_attr_.insert(std::pair<pthread_t,time_select*>(ts->thread_tid,ts));
            return NULL;
	    }
	
        //获取所有线程中运行最长时间
	    int GetTimeDifference()
	    {
		    //1.从map当中可以获取各个线程属性，计算各个线程并发完成的时间,计算出最大时间max_time
            std::map<pthread_t,time_select*>::iterator it = thread_attr_.begin();
            //int max_time = it->second->_time_sum;
            int max_time = 0;
            while(it != thread_attr_.end())
            {
                if(it->second->_time_sum > max_time)
                {
                    max_time = it->second->_time_sum;
                }
                it++;
            }
            return max_time;
	    }


    private:
        int _pthread;//线程数
        int _connect;//总连接数
        int _simultaneously;//并发数
        std::string _url;//域名

        int _num;//每个线程需要执行的请求数
        double _singletime;//每个请求之间的间隔时间

	    std::map<pthread_t,time_select*> thread_attr_;
	
        int _time;//时间差
        
        Socket *st;
        Select *ss;
        Http *hp;
};

