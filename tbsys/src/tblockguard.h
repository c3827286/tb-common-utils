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
     * @brief  CLockGuard��һ��ģ���࣬����ҪCThreadMutex��Ϊ����ģ�����
     * ���캯�����ô��������lock����,������������unlock����
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
