/*************************************************************************
    > File Name: cli.cpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年06月23日 星期二 12时41分48秒

    客户端
    1、创建套接字
    2、发起连接
    3、发送数据
    4、接收数据
    5、关闭套接字
 ************************************************************************/
#include "tcp_svr.hpp"
#define CHECK_RET(p) if(p == false){return 0;}//判断封装的接口是否调用成功，失败直接返回
int main()
{
    Tcpsvr tp;
    //1、创建套接字
    CHECK_RET(tp.Createsocket());
    //2、发起连接
    CHECK_RET(tp.Connect("192.168.163.129",18888));
    std::string buf;
    tp.Recv(&buf);
    printf("%s",buf.c_str());
    //5、关闭套接字
    tp.Close();
    return 0;
}
