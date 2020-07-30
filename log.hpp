#ifndef __LOG_HPP_
#define __LOG_HPP_

#include<iostream>
#include<sys/time.h>
#include<string>

#define Normal 1
#define Warning 2
#define Fatal 3

uint64_t GetTimeStamp()
{
    struct timeval time;
    if(gettimeofday(&time,nullptr)==0)
    {
        return time.tv_sec;
    }
    return 0;
}
void LOG(std::string level,std::string msg,std::string file_name,int num)
{
    std::cerr << "[" << level << "][" << GetTimeStamp() << "][" << msg << "][" << file_name << "][" << num<<"]"<<std::endl;

}

#define LOG(level,message) LOG(#level,message,__FILE__,__LINE__)
#endif
