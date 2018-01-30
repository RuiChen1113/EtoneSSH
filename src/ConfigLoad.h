/***************************************************************************
** 版权所有:  Copyright (c) 20016-2018  ********************             
** 文件名称:  ConfigLoad.h
** 文件标识: 
** 内容摘要:  
** 当前版本:  v1.0
** 作    者:  Gu Yingchun
** 完成日期: 2018年1月28日
***************************************************************************/

#ifndef _LOAD_CONF_H
#define _LOAD_CONF_H

#include <string>

typedef struct _ssh2_conf{
	std::string DstIp;
	int DstPort;
	std::string DstUsrname;
	std::string DstPassword;
}SSH2Conf;

class LoadConfig{
public:
	LoadConfig(const char * ConfigName);
	~LoadConfig();
	bool GetConf(SSH2Conf &pConf);
	bool Init();

private:
	std::string m_FileName;
	SSH2Conf m_Conf;
};

#endif

