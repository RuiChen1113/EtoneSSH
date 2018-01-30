#ifndef _WAFER_SINGLETON_H_
#define _WAFER_SINGLETON_H_

#include "LockMutex.h"

#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

class CSingletonBase
{
protected:
	class CInstanceTable : public list<CSingletonBase *>
	{
	public:
		CInstanceTable()
		{
			m_bIsClearing = false;
		};

		virtual ~CInstanceTable() 
		{
			m_bIsClearing = true;
			for_each(begin(), end(), DeleteInstance);
		}
		
	public:
		static void DeleteInstance(CSingletonBase * pInstance)
		{
			delete pInstance;
		}

	public:
		bool m_bIsClearing;
	};
	//end of nested class
	///////////////////////////////////////////////////////////


public:
	CSingletonBase() 
	{
		CSingletonBase::m_InstanceTbl.push_back(this);
	}

	virtual ~CSingletonBase() 
	{
		if(!m_InstanceTbl.m_bIsClearing)
			m_InstanceTbl.remove(this);	
	}

public:
	//static member
	static CInstanceTable m_InstanceTbl;
};


template <typename T>
class CSingleton : public CSingletonBase
{
public:
	// double check lock pattern.
	static T * GetInstance()
	{
		if(!m_pInstance)
		{
			LockMutex lockit(m_mtxInstance);
			if(!m_pInstance) //must check again!
			{
				m_pInstance = new T;
			}
		}

		return m_pInstance;
	}

protected:
	CSingleton()
	{
		//if(m_pInstance)
		//	throw runtime_error("More than one Instance!");
	}

	virtual ~CSingleton()
	{
		m_pInstance = NULL;
	}

private:
	static T *m_pInstance;
	static Mutex m_mtxInstance;
};


//must defined here.
//if defined in singleton.cpp there will be a link error.
//I think it is maybe because Singleton is a template class.
template<typename T> T * CSingleton<T>::m_pInstance = NULL;
template<typename T> Mutex CSingleton<T>::m_mtxInstance;

/*
usage:
class YourClass : public Singleton<YourClass>
{
protected://or private:  this will prevent programmer creating object directly
    friend class Singleton<YourClass>;
    YourClass(){};
public:
	virtual ~YourClass() {};
//and your class's specific members below:
...
}
*/

#endif  //_WAFER_SINGLETON_H_

