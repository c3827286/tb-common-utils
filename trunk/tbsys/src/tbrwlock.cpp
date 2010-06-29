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

#include "tbrwlock.h"

using namespace tbsys;

int CRLock::lock() const
{
    return pthread_rwlock_rdlock(m_rlock);
}

int CRLock::tryLock() const
{
    return pthread_rwlock_tryrdlock(m_rlock) ;
}

int CRLock::unlock() const
{
    return pthread_rwlock_unlock(m_rlock);
}

int CWLock::lock() const
{
    return pthread_rwlock_wrlock(m_wlock) ;
}

int CWLock::tryLock() const
{
    return pthread_rwlock_trywrlock(m_wlock);
}

int CWLock::unlock() const
{
    return pthread_rwlock_unlock(m_wlock);
}

//////////////////////////////////////////////////////////////////////////////////////
CRWLock::CRWLock()
{
    pthread_rwlockattr_t attr;
    pthread_rwlockattr_init(&attr);
    pthread_rwlock_init(&m_rwlock, &attr);
    
    m_rlock = new CRLock(&m_rwlock);
    m_wlock = new CWLock(&m_rwlock);
}

CRWLock::~CRWLock()
{
    pthread_rwlock_destroy(&m_rwlock);
    delete m_rlock;
    delete m_wlock;
}

//////////////////////////////////////////////////////////////////////////////////////
CRWSimpleLock::CRWSimpleLock()
{
    pthread_rwlockattr_t attr;
    pthread_rwlockattr_init(&attr);
    pthread_rwlock_init(&m_rwlock, &attr);
}

CRWSimpleLock::~CRWSimpleLock()
{
    pthread_rwlock_destroy(&m_rwlock);
}

int CRWSimpleLock::rdlock()
{
    return pthread_rwlock_rdlock(&m_rwlock);
}

int CRWSimpleLock::wrlock()
{
     return pthread_rwlock_wrlock(&m_rwlock);
}

int CRWSimpleLock::tryrdlock()
{
    return pthread_rwlock_tryrdlock(&m_rwlock);
}

int CRWSimpleLock::trywrlock()
{
    return pthread_rwlock_trywrlock(&m_rwlock);
}

int CRWSimpleLock::unlock()
{
    return pthread_rwlock_unlock(&m_rwlock);
}
