/***************************************************************************
** ��Ȩ����:  Copyright (c) 20016-2018  ********************             
** �ļ�����:  ConfigLoad.h
** �ļ���ʶ: 
** ����ժҪ:  
** ��ǰ�汾:  v1.0
** ��    ��:  Gu Yingchun
** �������: 2018��1��28��
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

