/*************************************************************************
    > File Name: http.hpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年10月02日 星期五 03时14分31秒
    > 描述：构造http请求，封装成一个字符串，用send给服务器发送
 ************************************************************************/
#pragma once
#include <iostream>
#include "url.hpp"
class Http
{
    public:
        Http()
        {

        }
        Http(std::string& _url)
        {

            head = "POST %s HTTP/1.1\r\n"
                    "Host: %s:%d\r\n"
                    "Content-Type: application/x-www-form-urlencoded\r\n"
                    "Content-Length: %d\r\n\r\n"
                    "%s";
            url = "http://";
            url += _url;
            UrltoAddress us(_url);
            host = us.Url();
            port = 80;
            msg = "aaa=1&bbb=2";
        }
        ~Http()
        {

        }
        std::string http()//构建好字符串，要想服务器发送的内容
        {
            char buf[1024]={0};
            sprintf(buf, head.c_str(), url.c_str(), host.c_str(), port, msg.size(), msg.c_str());
            int i = 0;
            int num = sizeof(buf);
            for(i=0;i<num;i++)
            {
                data += buf[i];
            }
            return data;
        }
    public:
            std::string head;
            std::string url;
            std::string host;
            int port;
            std::string msg;
            std::string data;
};
