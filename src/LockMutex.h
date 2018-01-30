#ifndef _ETONE_LOCK_MUTEX_H_
#define _ETONE_LOCK_MUTEX_H_

#include <pthread.h>

class Mutex
{
public:
	Mutex(){ pthread_mutex_init(&_mutex, NULL);}
	~Mutex(){ pthread_mutex_destroy(&_mutex);}

	void lock(void){ pthread_mutex_lock(&_mutex);}
	void unlock(void){ pthread_mutex_unlock(&_mutex);}

private:
	friend class LockMutex;
	pthread_mutex_t _mutex;
};

// read-write lock
class ReadWriteLock
{
public:
	ReadWriteLock(){ pthread_rwlock_init(&_rwLock, NULL);}
	~ReadWriteLock(){ pthread_rwlock_destroy(&_rwLock);}
	
	void readLock(void){ pthread_rwlock_rdlock(&_rwLock);}
	void writeLock(void){ pthread_rwlock_wrlock(&_rwLock);}
	void unlock(void){ pthread_rwlock_unlock(&_rwLock);}

protected:
	pthread_rwlock_t _rwLock;
};

// Lock mutex class.
class LockMutex
{
public:
	LockMutex(Mutex &mtx) : _mtx(mtx){ pthread_mutex_lock(&(_mtx._mutex));}
	~LockMutex(){ pthread_mutex_unlock(&(_mtx._mutex));}
private:
	Mutex &_mtx;
};

#endif //_ETONE_LOCK_MUTEX_H_

