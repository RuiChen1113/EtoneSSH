/***************************************************************************
** ��Ȩ����:  Copyright (c) 20016-2018  ********************             
** �ļ�����:  ssh2.h
** �ļ���ʶ: 
** ����ժҪ:  
** ��ǰ�汾:  v1.0
** ��    ��:  Gu Yingchun
** �������: 2018��1��29��
***************************************************************************/

#ifndef _SSH2_H_CLASS_
#define _SSH2_H_CLASS_
#include <libssh2.h>
#include <libssh2_sftp.h>
#include <string>


class Channel
{
public:
	Channel(LIBSSH2_CHANNEL *channel);
	~Channel(void);
	std::string Read( const std::string &strend = "", int timeout = 3000 );
	bool   Write(const std::string &data);
	
private:
	Channel(const Channel&);
	Channel operator=(const Channel&);
private:
	LIBSSH2_CHANNEL *m_channel;
};

class Ssh2{
public:
	Ssh2(const std::string &srvIp, int srvPort=22);
	~Ssh2(void);

	bool Connect( const std::string &userName, const std::string &userPwd);
	bool Disconnect(void);
	Channel* CreateChannel(const std::string &ptyType = "vanilla");	
public:  
	static void S_KbdCallback(const char*, int, const char*, int, int, const LIBSSH2_USERAUTH_KBDINT_PROMPT*, LIBSSH2_USERAUTH_KBDINT_RESPONSE*, void **a ); 
	static std::string s_password;

private:  
	std::string       m_srvIp;  
	int               m_srvPort;  
	std::string       m_userName;	
	std::string       m_password;	
	int               m_sock;	
	LIBSSH2_SESSION * m_session;  
};

#endif
