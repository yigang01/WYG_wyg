/*************************************************************************
    > File Name: main.hpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年10月09日 星期五 10时58分28秒
 ************************************************************************/

#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include "socket.hpp"
#include "select.hpp"
#include "http.hpp"

//线程属性类
typedef struct time_select
{
    int _time_sum;//线程运行时间
    pthread_t thread_tid;//线程标识符
    void *tl;
    struct timeval _start, _end;//计时
}time_select;

class HttpLoad
{
    public:
        HttpLoad()
        {
            pthread_num_ = 2;
            connect_num_ = 100;
            concurrent_num_ = 20;
            flag = 0;
            
            st = NULL;
            hp = NULL;
            ss = NULL;
        }
        ~HttpLoad()
        {
            if(st)
            {
                delete st;
            }

            if(hp)
            {
                delete hp;
            }
            if(ss)
            {
                delete ss;
            }
        }

        int InitSvr(int argc, char* argv[])
        {
            //获取参数
            int i; 
            for(i = 0; i < argc; i++)
            {
                if(strcmp(argv[i], "-p") == 0)
                {
                    pthread_num_ = atoi(argv[i+1]);
                }
                else if(strcmp(argv[i], "-c") == 0)
                {
                    connect_num_ = atoi(argv[i+1]);
                }
                else if(strcmp(argv[i], "-s") == 0)
                {
                    concurrent_num_ = atoi(argv[i+1]);
                }
            }
            url_ = argv[i-1];
            _num = connect_num_ / pthread_num_;
            //初始化其他服务
            st = new Socket(url_);
            if(!st)
            {
                printf("创建失败\n");
                return -1;
            }
            hp = new Http(url_);
            if(!hp)
            {
                printf("创建失败\n");
                return -1;
            }
            ss = new Select();
            if(!ss)
            {
                printf("创建失败\n");
                return -1;
            }
            return 0;
        }

	    //开启线程
	    int StartSvr()
	    {
	        pthread_t tid[pthread_num_];	
            for(int i = 0; i < pthread_num_; i++)
            {
                time_select *tt = new time_select();
                tt->tl = (void*)this;
                tt->thread_tid = tid[i];//获取到了当前线程的标识符
                int ret = pthread_create(&tid[i],NULL,ThreadStart,(void*)tt);
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
            time_select *ts = (time_select*)arg;
            HttpLoad* http_load_svr = (class HttpLoad*)ts->tl;
            //开始计时
            gettimeofday(&(ts->_start),NULL);
            //1、创建套接字
            http_load_svr->st->CreateSocket();
            //2、发起连接
            bool ret1 = http_load_svr->st->Connect(http_load_svr->hp->host,http_load_svr->hp->port);
            //3、设置socket为非阻塞
            //http_load_svr->st->setsocket();
            //4、添加该线程的套接字描述符到select中
            http_load_svr->ss->Addfd(http_load_svr->st->_sockfd);
            //5、发送数据
            pthread_mutex_lock(&(http_load_svr->st->_mutex));
            while(http_load_svr->_num)
            {
                usleep(http_load_svr->settime());//间隔时间
                bool ret2 = http_load_svr->st->Send(http_load_svr->hp->http());
                std::string buf;
                //http_load_svr->st->Recv(&buf);
                //printf("%s\n",buf.c_str());
                if(ret1 == true && ret2 == true)
                {
                    http_load_svr->st->sucessed ++;//连接和发送数据都成功了
                }
                http_load_svr->_num --;
            }

            pthread_mutex_unlock(&(http_load_svr->st->_mutex));
            //6、select进行监控
            std::vector<Socket> vec;
            http_load_svr->ss->selectwait(&vec);//进行监控
            for(size_t i = 0 ; i < vec.size(); i++)
            {
                std::string buf;
                bool ret = vec[i].Recv(&buf);
                if(!ret)
                {
                    http_load_svr->ss->Deletefd(vec[i].Getfd());
                    vec[i].Close();            
                }         
            }
            //5、关闭套接字
            http_load_svr->st->Close();
            //结束计时
            //http_load_svr->end_time();
            gettimeofday(&(ts->_end),NULL);
            int timeuse = 1000000 *( ts->_end.tv_sec - ts->_start.tv_sec) + ts->_end.tv_usec -ts->_start.tv_usec;
            ts->_time_sum = timeuse;
            http_load_svr->st->_time = timeuse;
            http_load_svr->thread_attr_.insert(std::pair<pthread_t,time_select*>(ts->thread_tid,ts));
            return NULL;
	    }
	
        //遍历map找到线程运行最大时间，再进行相关计算
        int result()
        {
            sleep(15);
            auto it = thread_attr_.begin();
            int max_time = 0;
            while(it != thread_attr_.end())
            {
                if(it->second->_time_sum > max_time)
                {
                    max_time = it->second->_time_sum;
                }
                it++;
            }
            printf("解析后的ip地址为：%s\n",hp->host.c_str());
            printf("每秒完成的http连接数为：%d\n",(int)((st->sucessed * 1000000)/max_time));
            flag = 1;
            return flag;
        }
        double settime()//计算间隔时间
        {
            double sec = connect_num_ / concurrent_num_;
            _singletime = (sec / connect_num_) * 1000000;
            return _singletime;
        }
    private:
        int pthread_num_;//线程数
        int connect_num_;//总连接数
        int concurrent_num_;//并发数

        std::string url_;//域名

        int _num;//每个线程需要执行的请求数
        double _singletime;//每个请求之间的间隔时间

	    std::map<pthread_t,time_select*> thread_attr_;//key值为线程标识符，value为线程属性
	
        int _time;//时间差
        
        int flag;//标志位
        
        Socket *st;
        Select *ss;
        Http *hp;
};

