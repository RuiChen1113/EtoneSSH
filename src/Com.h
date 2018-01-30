/***************************************************************************
** 版权所有:  Copyright (c) 20016-2018  ********************             
** 文件名称:  Com.h
** 文件标识: 
** 内容摘要:  
** 当前版本:  v1.0
** 作    者:  Gu Yingchun
** 完成日期: 2018年1月28日
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
