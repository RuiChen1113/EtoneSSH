/***************************************************************************
** 版权所有:  Copyright (c) 20016-2018  ********************             
** 文件名称:  ConfigLoad.cpp
** 文件标识: 
** 内容摘要:  
** 当前版本:  v1.0
** 作    者:  Gu Yingchun
** 完成日期: 2018年1月28日
***************************************************************************/

#include <string>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

#include "Log.h"
#include "ConfigLoad.h"
#include "ConfigCom.h"

using namespace std;

LoadConfig::LoadConfig(const char * ConfigName)
{
	if(ConfigName)
		m_FileName = ConfigName;
	else
		m_FileName = "./EtoneSsh2.conf";
}

LoadConfig::~LoadConfig()
{

}

bool LoadConfig::Init()
{
    if(m_FileName.length() > 0 && access(m_FileName.c_str(), R_OK) != -1)
    {
        cout<<"Load "<<m_FileName<<"..."<<endl;
    }else{
        CLog* pLog = CLog::GetInstance();
        pLog->Log(CLog::INFO, "%s : is invailed\n", m_FileName.c_str());
        return false;
    }

    Config configSettings(m_FileName);

    m_Conf.DstIp       = configSettings.Read("ssh2_dest_ip"      , m_Conf.DstIp);
    m_Conf.DstPort     = configSettings.Read("ssh2_dest_port"    , m_Conf.DstPort);
    m_Conf.DstUsrname  = configSettings.Read("ssh2_usr_name"     , m_Conf.DstUsrname);
    m_Conf.DstPassword = configSettings.Read("ssh2_usr_password" , m_Conf.DstPassword);

    return true;
}

bool LoadConfig::GetConf(SSH2Conf &pConf)
{
    pConf = m_Conf;
    return true;
}

