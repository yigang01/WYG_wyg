/*************************************************************************
    > File Name: con_pro.cpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年06月23日 星期二 09时30分56秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<queue>
using namespace std;
#define PTHREADCOUNT 1
//1、创建一个队列
class Blockqueue
{
    public:
        Blockqueue(int capacity = 1)
        {
            _capacity = capacity;
            pthread_mutex_init(&_mutex,NULL);
            pthread_cond_init(&_pro_cond,NULL);
            pthread_cond_init(&_con_cond,NULL);
        }
        ~Blockqueue()
        {
            pthread_mutex_destroy(&_mutex);
            pthread_cond_destroy(&_pro_cond);
            pthread_cond_destroy(&_con_cond);
        }
        void Push(int& data)//生产者进行生产
        {
            pthread_mutex_lock(&_mutex);//保证互斥
            while(que.size() >= _capacity)
            {
                pthread_cond_wait(&_pro_cond,&_mutex);//保证同步
            }
            que.push(data);
            printf("pro_start : [%p] [%d]\n",pthread_self(),data);
            pthread_mutex_unlock(&_mutex);
            pthread_cond_signal(&_con_cond);
        }
        void Pop(int *data)//消费者去消费
        {
            pthread_mutex_lock(&_mutex);//保证互斥
            while(que.empty())
            {
                pthread_cond_wait(&_con_cond,&_mutex);//保证同步
            }
            *data = que.front();
            que.pop();
            pthread_mutex_unlock(&_mutex);
            pthread_cond_signal(&_pro_cond);
        }
    private:
        std::queue<int> que;
        pthread_mutex_t _mutex;
        pthread_cond_t _pro_cond;
        pthread_cond_t _con_cond;
        size_t _capacity;
};
int i = 0;
void* pro_start(void *arg)//生产者
{
    Blockqueue *bq = (Blockqueue*)arg;
    while(1)
    {
        bq->Push(i);
        i++;
    }
    return NULL;
}
void* con_start(void *arg)//消费者
{
    Blockqueue *bq = (Blockqueue*)arg;
    while(1)
    {
        int i;
        bq->Pop(&i);
        printf("con_start : [%p] [%d]\n",pthread_self(),i);
    }
}
int main()
{
    pthread_t con_tid[PTHREADCOUNT];
    pthread_t pro_tid[PTHREADCOUNT];
    Blockqueue *bq = new Blockqueue();
    int i = 0;
    for(i = 0; i < PTHREADCOUNT; i++)
    {
        int ret = pthread_create(&pro_tid[i],NULL,pro_start,(void*)bq);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
        ret = pthread_create(&con_tid[i],NULL,con_start,(void*)bq);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
    }
    for(i = 0; i < PTHREADCOUNT; i++)
    {
        pthread_join(pro_tid[i],NULL);
        pthread_join(con_tid[i],NULL);
    }
    return 0;
}
