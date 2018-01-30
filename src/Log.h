#ifndef _ETONE_LOG_H_
#define _ETONE_LOG_H_

#include <stdio.h>
#include <map>
#include <stdarg.h>

#include "Singleton.h"
#include "LockMutex.h"

#define LOG_FILE_PATH	"//tmp//"
#define LOG_FILE_NAME	"EtoneSSH2.log"
#define LOG_BUFFER_MAX_LEN 8192

// Log class.
class CLog: public CSingleton<CLog>
{
public:
	enum LEVEL
	{
		FATAL = 0,
		ERR,
		WARN,
		INFO,
		TRACE,
		DEBUG
	};

	enum RESULT
	{
		RESULT_OK = 0,
		RESULT_FAILED
	};

	enum INITCODE
	{
		INIT_OK = 0,
		INIT_FAILED = 1,
		INIT_DIRNOTEXIST = 2,
		INIT_OPENFILEFAILED = 3
	};

protected:
	friend class CSingleton<CLog>;
	CLog();

public:
	~CLog();

	//write log informations.
	int Log(LEVEL lvl, const char *msg, ...);

	// open log file and then ready to write log infomations.
	bool Init(void);

	void SetLogLevel(LEVEL lvl);
	void SetLogLevel(string& strLevel);

	// get log vevel.
	LEVEL GetLogLevel(void);

private:
	int vlog(LEVEL lvl, const char *fmt, va_list ap);

private:
	// file stream.
	FILE *m_pLogFile;
	// current log file name;
	string m_strCurLogFileName;
	
	// log level for config file.
	LEVEL m_LogLevel;

private:
	// enum LEVEL and string log level mapping.
	typedef map<string, int>::iterator LevelMapItr;
	map<string, int> m_LevelMap;
	
private:
	Mutex m_mtxLog;
};

#endif // _ETONE_LOG_H_

