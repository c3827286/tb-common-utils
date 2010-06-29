/*
 * (C) 2007-2010 Taobao Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *
 * Version: $Id$
 *
 * Authors:
 *   duolong <duolong@taobao.com>
 *
 */

#ifndef TBSYS_RW_LOCK_H
#define TBSYS_RW_LOCK_H

#include <pthread.h>
#include "tblockguard.h"

namespace tbsys
{
	/** 
	 * @brief linux线程 读写锁中的读锁的封装
	 */
	class CRLock
	{
	public:
		CRLock(pthread_rwlock_t* lock) : m_rlock(lock) {}
		~CRLock(){}
		
		/** 
		 * @brief 加锁
		 * 
		 * @return 
		 */
		int lock() const;
		/** 
		 * @brief 尝试加锁
		 * 
		 * @return 
		 */
		int tryLock() const;
		/** 
		 * @brief 解锁
		 * 
		 * @return 
		 */
		int unlock() const;
		
	private:
		mutable pthread_rwlock_t* m_rlock;
	};

	/** 
	 * @brief linux 线程读写锁中的写锁的封装
	 */
	class CWLock
	{
	public:
		CWLock(pthread_rwlock_t* lock) : m_wlock(lock) {}
		~CWLock(){}
		
		int lock() const;
		int tryLock() const;
		int unlock() const;
		
	private:
		mutable pthread_rwlock_t* m_wlock;
	};	

	class CRWLock 
	{
	public:
		CRWLock();
		~CRWLock();

		CRLock* rlock() const {return m_rlock;}; 
		CWLock* wlock() const {return m_wlock;}; 

	private:
		CRLock* m_rlock;
		CWLock* m_wlock;
		mutable pthread_rwlock_t m_rwlock;
	};

	/** 
	 * @brief 对linux线程锁中的读写锁封装
	 */
	class CRWSimpleLock
	{
	public:
	    CRWSimpleLock();
	    ~CRWSimpleLock();
		
	    int rdlock();
	    int wrlock();
		int tryrdlock();
		int trywrlock();
		int unlock();
		
	private:    
	    pthread_rwlock_t m_rwlock;
	};

	/** 
	 * @brief linux 线程锁中读锁的助手类
	 */
	class CRLockGuard
	{
	public:
		CRLockGuard(CRWLock& rwlock,bool block = true) : m_guard( ( *rwlock.rlock() ) ,block) {}
		~CRLockGuard(){}

		bool LockStatus()
		{
			return m_guard.LockStatus();
		}

	private:
		CLockGuard<CRLock> m_guard;
	};
	
	/** 
	 * @brief linux 线程锁中写锁的助手类
	 */
	class CWLockGuard
	{
	public:
		CWLockGuard(CRWLock& rwlock,bool block = true) : m_guard( ( *rwlock.wlock() ) ,block) {}
		~CWLockGuard(){}

		bool LockStatus()
		{
			return m_guard.LockStatus();
		}

	private:
		CLockGuard<CWLock> m_guard;
	};
}

#endif
