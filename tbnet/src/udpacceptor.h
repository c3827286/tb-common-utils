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

#ifndef TBNET_TCPACCEPTOR_H_
#define TBNET_TCPACCEPTOR_H_

namespace tbnet {

class UDPAcceptor : public UDPComponent {

public:
    /**
    * 构造函数，由Transport调用。
    * 输入:
    *  transport:  运输层对象:::spec: 格式 [upd|tcp]:ip:port
    *  streamer:  数据包的双向流，用packet创建，解包，组包。
    * serverAdapter: 用在服务器端，当Connection初始化及Channel创建时回调时用
    */
    UDPAcceptor(Transport *owner, char *spec, IPacketStreamer *streamer, IServerAdapter *serverAdapter);

    /**
    * 当有数据可读时被Transport调用
    * 返回
    * 是否成功, true - 成功, false - 失败。
    */
    bool handleReadEvent();

    /**
    * 不用
    */
    bool handleWriteEvent() {
        return false;
    }
};
}

#endif /*TCPACCEPTOR_H_*/
