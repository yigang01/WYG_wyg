/*************************************************************************
    > File Name: svr.cpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年06月23日 星期二 12时25分14秒

    服务端
    1、创建套接字
    2、绑定地址信息
    3、监听
    4、获取链接
    5、接收数据
    6、发送数据
    7、关闭套接字
 ************************************************************************/

#include "tcp_svr.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/stat.h>
#define CHECK_RET(p) if(p == false){return 0;}//判断封装接口是否调用成功，失败直接返回
int main()
{
    Tcpsvr tp;
    //1、创建套接字
    CHECK_RET(tp.Createsocket());
    //2、绑定地址信息
    CHECK_RET(tp.Bind("192.168.163.129",18888));
    //3、监听
    CHECK_RET(tp.Listen());
    Tcpsvr newts;
    while(1)
    {
        //4、获取连接
        struct sockaddr_in cli_addr;
        CHECK_RET(tp.Accept(&newts,&cli_addr));
        //5、打开文件
        int file_fd = open("./wyg.txt",O_RDWR | O_CREAT,664);
        if(file_fd < 0)
        {
            perror("open");
            return -1;
        }
        //6、把目标文件传递给服务器
        struct stat stat_buf;//设置file_fd文件描述符属性
        fstat(file_fd,&stat_buf);
        int ret = sendfile(newts.GetFd(),file_fd,NULL,stat_buf.st_size);//把目标文件传递给服务器
        if(ret < 0)
        {
            perror("sendfile");
            return -1;
        }
    }
    //7、关闭套接字
    tp.Close();
    newts.Close();
    return 0;
}

