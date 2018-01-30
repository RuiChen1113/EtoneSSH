/***************************************************************************
** ��Ȩ����:  Copyright (c) 20016-2018  ********************             
** �ļ�����:  Com.h
** �ļ���ʶ: 
** ����ժҪ:  
** ��ǰ�汾:  v1.0
** ��    ��:  Gu Yingchun
** �������: 2018��1��28��
***************************************************************************/

#ifndef _ETONE_COM_H
#define _ETONE_COM_H

#include <string>

struct Parameter{
	char * UsrName;
	char * PassWord;
    char * ConfigFileName;
    char * CmdFileName;
    char * DstIp;
    int DstPort;
    char * CMD;
	int DebugLevel;
};

bool parse_commandline(struct Parameter *pParameter, int argc, char **argv);
bool is_valid_gParameter(struct Parameter *pParameter);
void StrToHex(unsigned char *pbDest, char *pbSrc, int nLen);
std::string  GetString(int I);
std::string  GetString(double d);

#endif
