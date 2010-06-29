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

#ifndef TBSYS_LOCK_GUARD_H_
#define TBSYS_LOCK_GUARD_H_

namespace tbsys
{
    /** 
     * @brief  CLockGuard是一个模板类，它需要CThreadMutex作为它的模板参数
     * 构造函数调用传入参数的lock方法,析构函数调用unlock方法
     */
    template <class LLOCK>
    class CLockGuard
    {
        public:
        CLockGuard(LLOCK& lock , bool block = true) : m_lock(lock)
        {
            m_result = block ? m_lock.lock() : m_lock.tryLock();
        }
        ~CLockGuard()
        {
            m_lock.unlock();
        }

        bool LockStatus()
        {
            return (m_result == 0);
        }
        
    private:
        LLOCK& m_lock;
        int m_result;
    };
}

#endif
