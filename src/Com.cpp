/***************************************************************************
** ��Ȩ����:  Copyright (c) 20016-2018  ********************             
** �ļ�����:  Com.h
** �ļ���ʶ: 
** ����ժҪ:  
** ��ǰ�汾:  v1.0
** ��    ��:  Gu Yingchun
** �������: 2018��1��28��
***************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#include "Com.h"
#include "Log.h"


bool is_valid_mac(const char *DevCode);
bool is_valid_ip(const char *ip);

/** Uses getopt() to parse the command line and set configuration values
 * also populates restartargv
 */
bool parse_commandline(struct Parameter *pParameter, int argc, char **argv)
{
    int c;
	while (-1 != (c = getopt(argc, argv, "C:c:d:h:p:l:U:P:"))) {
		switch (c) {
            case 'C':
				if (optarg) {
					pParameter->CmdFileName= strdup(optarg);
				}
				break;
			case 'c':
				if (optarg) {
					pParameter->ConfigFileName= strdup(optarg);
				}
				break;
            case 'U':
				if (optarg) {
					pParameter->UsrName= strdup(optarg);
				}
				break;
            case 'P':
                if (optarg) {
                    pParameter->PassWord= strdup(optarg);
                }
                break;
			case 'h':
				if (optarg) {
					pParameter->DstIp= strdup(optarg);
				}
				break;
			case 'p':
				if (optarg) {
					pParameter->DstPort= atoi(optarg);
				}
				break;
			case 'd':
	            if (optarg) {
	                pParameter->DebugLevel = atoi(optarg);
	            }
	         	break;
            case 'l':
	            if (optarg) {
	                pParameter->CMD = strdup(optarg);
	            }
	         	break;
                
			default:
				return false;
		}
	}
	return true;
}

bool is_valid_gParameter(Parameter *pParameter)
{
}

bool is_valid_mac(const char *DevCode)
{
    const int MAC_LEN = 12;
	if(MAC_LEN != strlen(DevCode))
	{
		return false;

	}
	return true;
}

bool is_valid_ip(const char *ip)
{
    int section = 0;  //ÿһ�ڵ�ʮ����ֵ
    int dot = 0;       //������ָ���
    int last = -1;     //ÿһ������һ���ַ�
    while(*ip){
        if(*ip == '.' || *ip == '\0'){
            dot++;
            if(dot > 3){
                return false;
            }
            if(section >= 0 && section <=255){
                section = 0;
            }else{
                return false;
            }
        }else if(*ip >= '0' && *ip <= '9'){
            section = section * 10 + *ip - '0';
            if(last == '0'){
                return false;
            }
        }else{
            return false;
        }
        last = *ip;
        ip++;       
    }

    if(section >= 0 && section <=255){
        section = 0;
    }
    return section ? false : true;
}


/*
// C prototype : void StrToHex(BYTE *pbDest, BYTE *pbSrc, int nLen)
// parameter(s): [OUT] pbDest - ���������
// [IN] pbSrc - �ַ���
// [IN] nLen - 16���������ֽ���(�ַ����ĳ���/2)
// return value:
// remarks : ���ַ���ת��Ϊ16������
*/


void StrToHex(unsigned char *pbDest, char *pbSrc, int nLen)
{
	char h1,h2;
	unsigned char s1,s2;
	int i;

	for (i=0; i<nLen; i++)
	{
		h1 = pbSrc[2*i];
		h2 = pbSrc[2*i+1];

		s1 = toupper(h1) - 0x30;
		if (s1 > 9)
		s1 -= 7;

		s2 = toupper(h2) - 0x30;
		if (s2 > 9)
		s2 -= 7;

		pbDest[i] = s1*16 + s2;
	}
}

string  GetString(int I)
{
	char tmp[32] = {0};
	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "%d", I);
	return string(tmp);
}

string  GetString(double xyz)
{
	char tmp[32] = {0};
	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "%.02f", xyz);
	return string(tmp);
}


