
#include <sys/types.h> 
#include <sys/stat.h> 
#include <errno.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "Log.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// class CLog implemetions.

CLog::CLog()
{
	m_LevelMap.insert(make_pair(string("FATAL"), 0));
	m_LevelMap.insert(make_pair(string("ERR"), 1));
	m_LevelMap.insert(make_pair(string("WARN"), 2));
	m_LevelMap.insert(make_pair(string("INFO"), 3));
	m_LevelMap.insert(make_pair(string("DEBUG"), 4));
	m_LogLevel = DEBUG;
	m_pLogFile = NULL;
	m_strCurLogFileName = LOG_FILE_PATH;
    m_strCurLogFileName += LOG_FILE_NAME;
	Init();
}

CLog::~CLog()
{
	if (m_pLogFile)
		fclose(m_pLogFile);
}

bool CLog::Init()
{
	bool bRet = true;

#ifdef WIN32
	_mkdir(LOG_FILE_PATH);
#else
	mkdir(LOG_FILE_PATH, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif	
	if((m_pLogFile = fopen(m_strCurLogFileName.c_str(), "a+")) == NULL)
	{
		cout<<"open log file \" " <<m_strCurLogFileName.c_str()<< " \" failed" <<endl;
		bRet = false;
	}

	return bRet;
}

void CLog::SetLogLevel(LEVEL lvl)
{
	m_LogLevel = lvl;
}

void CLog::SetLogLevel(string& strLevel)
{
	LevelMapItr itr;

	itr = m_LevelMap.find(strLevel);
	if (itr != m_LevelMap.end())
	{
		m_LogLevel = (LEVEL)itr->second;
	}
	else
	{
		m_LogLevel = INFO;
	}
}

CLog::LEVEL CLog::GetLogLevel(void)
{
	return m_LogLevel;
}

int CLog::Log(LEVEL lvl, const char *msg, ...)
{
	if (!m_pLogFile && !Init())
	{
		printf("Open Log Fail!\n");
		return CLog::RESULT_FAILED;
	}

	va_list ap;
	int r;

	va_start(ap, msg);
	r = vlog(lvl, msg, ap);
	va_end(ap);

	return r;
}

// private functions.
int CLog::vlog(LEVEL lvl, const char *fmt, va_list ap)
{

	static char lvl2Str[][10] = {"FATAL", "ERROR", "WARN ", "INFO ", "TRACE", "DEBUG"};
	
	// if lvl information greater than level configured, then return.
	if(lvl > m_LogLevel)
		return RESULT_OK;
	
	// thread safe.
	LockMutex mtx(m_mtxLog);

	char buffer[LOG_BUFFER_MAX_LEN] = {0};

	time_t currtime;
	time(&currtime);
	tm *s_tm = localtime(&currtime);
	string tmstr = asctime(s_tm);
	
	string msg = tmstr + string(": [") + string(lvl2Str[lvl]) + string("] : ");
	int len = msg.length();
	
	memcpy(buffer, msg.c_str(), len);

#ifdef WIN32
	_vsnprintf(buffer + len, sizeof(buffer) - len - 1, fmt, ap);
#else
	vsnprintf(buffer + len, sizeof(buffer) - len - 1, fmt, ap);
#endif

	// Filter out characters not in Latin-1.
	unsigned char *p;
	for (p = (unsigned char *) buffer; *p != '\0'; p++) {
		if (*p == '\r' || *p == '\n')
			*p = ' ';
		else if (*p < 32 || (*p >= 128 && *p <= 160))
			*p = '?';
	}
	strcat(buffer, "\n");
	
	if (m_LogLevel >= DEBUG) 
		printf("%s", buffer + len);

	fputs(buffer, m_pLogFile);
	fflush(m_pLogFile);

	return RESULT_OK;
}
