/*************************************************************************
    > File Name: jarvis.hpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年07月15日 星期三 13时53分55秒
 ************************************************************************/
#ifndef __JARVIS_HPP_
#define __JARVIS_HPP_

#include<iostream>
#include<string>
#include<memory>
#include<map>
#include<unordered_map>
#include<sstream>
#include<json/json.h>
#include"speech/speech.h"
#include "speech/base/http.h"
#include"log.hpp"
#define SIZE 1024
using namespace std;

class Tulin
{
    public:
        Tulin()
        {

        }
        ~Tulin()
        {

        }
        string ResponsePickup(string& response)
        {
            JSONCPP_STRING errs;
            Json::Value root;
            Json::CharReaderBuilder rb;
            unique_ptr<Json::CharReader> jsonreader(rb.newCharReader());
            bool ret = jsonreader->parse(response.data(),response.data() + response.size(),&root,&errs);
            if(!ret || !errs.empty())
            {
                LOG(Warning,"jsoncpp parse error");
                return errs;
            }
            Json::Value results = root["results"];
            Json::Value values = results[0]["values"];
            return values["text"].asString();
        }
        string chat(string &massage)
        {
            Json::Value root;
            Json::Value use;
            Json::Value text1;
            Json::Value it;
            root["reqType"] = 0;
            it["text"] = massage;
            text1["inputText"] = it;
            root["perception"] = text1;
            use["apiKey"] = _apiKey;
            use["userId"] = _userId;
            root["userInfo"] = use;
            Json::StreamWriterBuilder wb;
            ostringstream os;
            unique_ptr<Json::StreamWriter> jsonwrite(wb.newStreamWriter());
            jsonwrite->write(root,&os);
            string body = os.str();
            string response;
            int code = client.post (url,nullptr,body,nullptr,&response);
            if(code != CURLcode::CURLE_OK)
            {
                LOG(Warnign,"http request error");
                return "";
            }
            return ResponsePickup(response);//response是一个json字符串，需要转换成反序列化
        }
    private:
        string _apiKey = "4449ad2d543b4e45aaa80e17fc55331c";
        string _userId = "1";
        string url = "http://openapi.tuling123.com/openapi/api/v2";
        aip::HttpClient client;
};


class Jarvis
{
    public:
        Jarvis()
            :client(nullptr)
        {}
        void Init()
        {
            client = new aip::Speech(AppID,APIKey,SecretKey);
            LoadCommand();
        }
        void LoadCommand()
        {
            string name = "./command.etc";
            ifstream in(name);
            if(!in.is_open())
            {
                LOG(Warning,"open error");
                exit(1);
            }
            char line[SIZE];
            string step = "：";
            while(in.getline(line,sizeof(line)))
            {
                string str = line;
                size_t pos = str.find(step);
                if(pos == string::npos)
                {
                    LOG(Warning,"find error");
                    break;
                }
                string key = str.substr(0,pos);
                string value = str.substr(pos + step.size());
                load_map.insert(make_pair(key,value));
                in.close();
            }
        }
        bool iscommand(string& message)
        {
            return load_map.find(message) != load_map.end() ? true:false;
        }
        bool Exec(string& command,bool is_print)
        {
            FILE *fp = popen(command.c_str(),"r");
            if(fp == nullptr)
            {
                LOG(Warning,"popen error");
                return false;
            }
            if(is_print)
            {
                char c;
                size_t s = 0;
                while((s = fread(&c,1,1,fp)) > 0)
                {
                    cout << c;
                }
            }
            pclose(fp);
            return true;
        }
        string ASR(aip::Speech *client)
        {
            string asr_file = "./voice/asr.wav";
            map<string,string> options;
            string file_content;
            aip::get_file_content(asr_file.c_str(),&file_content);
            Json::Value root = client->recognize(file_content,"wav",16000,options);
            return RecognizePickup(root);
        }
        bool TTL(aip::Speech *client,string& str)
        {
            ofstream ofile;
            string ttl = "./voice/ttl.mp3";
            ofile.open(ttl.c_str(),ios::out | ios::binary);
            string file_ret;
            map<string,string> options;
            options["spd"] = "6";
            options["per"] = "4";
            options["vol"] = "8";
            Json::Value result = client->text2audio(str,options,file_ret);
            if(!file_ret.empty())
            {
                ofile << file_ret;
            }
            else
            {
                cout << result.toStyledString() << endl;
            }
            ofile.close();
            return true;
        }
        string RecognizePickup(Json::Value &root)
        {
            int err_no = root["err_no"].asInt();
            if(err_no != 0)
            {
                cout << root["err_msg"] << " : " << err_no << endl;
                return "unKnow";
            }
            return root["result"][0].asString();
        }
        void run()
        {
            for(;;)
            {
                if(Exec(cmd,false))
                {
                    string message = ASR(client);
                    if(message == "退出。")
                    {
                        LOG(Normal,"好的");
                        break;
                    }
                    if(iscommand(message))
                    {
                        //是一个命令
                        LOG(Normal,"Exec a command");
                        Exec(load_map[message],false);
                        continue;
                    }
                    else
                    {
                        //不是一个命令
                        LOG(Normal,"run a normal chat");
                        LOG(Normal,message);
                        string echo = tl.chat(message);
                        LOG(Normal,echo);
                        TTL(client,echo);
                        Exec(play,false);
                    }
                }
            }
        }
    private:
        Tulin tl;
        aip::Speech *client;
        string AppID = "21519076";
        string APIKey = "ZME3TcQQnCEORpdSD7dFFZCv";
        string SecretKey = "ELmfomojLmyGLXv9P5x9QGpmnYF1tVkR";
        string cmd = "arecord -t wav -c 1 -r 16000 -d 5 -f S16_LE ./voice/asr.wav";
        string play = "cvlc --play-and-exit ./voice/ttl.mp3";
        unordered_map<string,string> load_map;
};


#endif
