/***************************************************************************
** 版权所有:  Copyright (c) 20016-2018  ********************             
** 文件名称:  main.cpp
** 文件标识: 
** 内容摘要:  
** 当前版本:  v1.0
** 作    者:  Gu Yingchun
** 完成日期: 2018年1月28日
***************************************************************************/

#if 0
#include <iostream>
#include <string>
#include "Ssh2.h"  
using namespace std;
int main(int argc, const char * argv[])  
{  
    Ssh2 ssh("127.0.0.1");  
    ssh.Connect("guyc","123456");
    Channel* channel = ssh.CreateChannel();
    //cout<<channel->Read()<<endl;
    channel->Write("uptime");  
    cout<<channel->Read("$")<<endl;   
    delete channel;  
    return 0;  
}  

#else
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Com.h"
#include "ConfigLoad.h"
#include "Log.h"
#include "Ssh2.h"

using namespace std;

struct Parameter gParameter;

void PRINTF_HELP()
{  
    printf("usage: EtoneSsh\n");
    printf("                -C cmdFileName\n");
    printf("                -c configFileName\n");
    printf("                -h hsotip\n");
    printf("                -p port\n");
    printf("                -U usrname\n");
    printf("                -P password\n");
    printf("                -d debug\n"); 
    printf("                -l cmdLine\n");
}

static void split(const string& src, const string& separator, vector<string>& dest);

int main(int argc, char **argv){
    PRINTF_HELP();
    int ret = -1;

    SSH2Conf ssh2Config;
    struct Parameter *pParameter = &gParameter;
    memset(pParameter, 0, sizeof(struct Parameter));
    parse_commandline(pParameter, argc, argv);
    
    if(!pParameter->ConfigFileName)
    {
        return -1;
    }
    LoadConfig config(pParameter->ConfigFileName);
    if(!config.Init())
    {
        CLog* pLog = CLog::GetInstance();
        pLog->Log(CLog::INFO, "config.Init() failed!\n");
        return -1;
    }
    config.GetConf(ssh2Config);


    if(NULL != pParameter->DstIp)
    {
        cout <<"pParameter->DstIp =  "<<pParameter->DstIp<< endl;
        ssh2Config.DstIp = pParameter->DstIp;
    }
    if(pParameter->DstPort > 0)
        ssh2Config.DstPort = pParameter->DstPort;
    if(NULL != pParameter->UsrName)
        ssh2Config.DstUsrname = pParameter->UsrName;
    if(NULL != pParameter->PassWord)
        ssh2Config.DstUsrname = pParameter->PassWord;
    
    cout<<pParameter->ConfigFileName<<endl;
    cout<<ssh2Config.DstIp<<endl;
    cout<<ssh2Config.DstPort<<endl;
    cout<<ssh2Config.DstUsrname<<endl;
    cout<<ssh2Config.DstPassword<<endl;

    Ssh2 ssh(ssh2Config.DstIp, ssh2Config.DstPort); 

    if(!ssh.Connect(ssh2Config.DstUsrname, ssh2Config.DstPassword))
    {
        CLog* pLog = CLog::GetInstance();
        pLog->Log(CLog::INFO, "ssh2.connect() failed :");
        return -1;
    }
    cout<<"ssh2.connect() ok"<<endl;
    Channel* pChannel = ssh.CreateChannel();
    if(NULL == pChannel)
    {
        CLog* pLog = CLog::GetInstance();
        pLog->Log(CLog::INFO, "config.Init() failed!\n");
        return -1;
    }
    vector<string> cmds;
    if(NULL != pParameter->CMD)
    {
        split(string(pParameter->CMD),";",cmds);
    }
    else if(NULL != pParameter->CmdFileName){
        ifstream file;
        file.open(pParameter->CmdFileName, ios::in);
        if(!file.is_open())
        {
            CLog* pLog = CLog::GetInstance();
            pLog->Log(CLog::INFO, "%s open failed!\n", pParameter->CmdFileName);  
        }
        string readline;
        while(getline(file, readline))
        {
            cmds.push_back(readline);
        }
    }
    if(cmds.size()>0)
    {
        string result;
        for(int i=0; i< cmds.size(); i++)
        {
            pChannel->Write(cmds[i]);
            usleep(1000*10);
            result = pChannel->Read();
            if(string::npos != result.find("error"))
            {
                cout<<"exec cmd "<<cmds[i]<<" "<< result <<endl;
                return -1;
            }else
                cout<<result<<endl;
        }
    }
    delete pChannel;
    return 0;
}

void split(const string& src, const string& separator, vector<string>& dest)
{
	string str = src;
	string substring;
	string::size_type start = 0, index;
	do
	{
		index = str.find_first_of(separator,start);
		if (index != string::npos)
		{    
			substring = str.substr(start,index-start);
			dest.push_back(substring);
			start = str.find_first_not_of(separator,index);
			if (start == string::npos) return;
		}
		else
		{
			//printf("not find %s\r\n",str.c_str());
		}
	}while(index != string::npos);

	//the last token
	substring = str.substr(start);
	dest.push_back(substring);
}

#endif
