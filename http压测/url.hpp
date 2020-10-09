/*************************************************************************
    > File Name: url.hpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年10月02日 星期五 03时14分31秒
    > 描述：进行域名解析的，把域名解析成ip地址
 ************************************************************************/

#pragma once
#include <iostream>
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>

class UrltoAddress//进行url解析
{
    public:
        UrltoAddress(const std::string &ip)
        {
            ptr = ip;
        }
        ~UrltoAddress()
        {

        }
        std::string Url()//进行url解析，返回解析后的ip地址
        {

            if( (hptr = gethostbyname(ptr.c_str()) ) == NULL  )
            {
                printf("gethostbyname error for host:%s\n", ptr.c_str());
                return "";
            }
            switch(hptr->h_addrtype)
            {
                case AF_INET:
                case AF_INET6:
                    pptr=hptr->h_addr_list;
                    std::string address = inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str));
                    //printf("%s\n",address.c_str());
                    return address;
                    break;
            }
            return "";
        }
    private:
        char **pptr;
        std::string ptr;
        char str[32];
        struct hostent *hptr;
};

