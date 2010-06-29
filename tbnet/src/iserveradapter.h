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

#ifndef TBNET_ISERVERADAPTER_H
#define TBNET_ISERVERADAPTER_H

namespace tbnet {

class IServerAdapter {
    friend class Connection;
    friend class TCPConnection;
public:
    // ����packet�ص�
    virtual IPacketHandler::HPRetCode handlePacket(Connection *connection, Packet *packet) = 0;
    // ����packet�ص�
    virtual bool handleBatchPacket(Connection *connection, PacketQueue &packetQueue) {
        return false;
    }
    // ���캯��
    IServerAdapter() {
        _batchPushPacket = false;
    }
    // ��������
    virtual ~IServerAdapter() {}
    // setBatch()
    void setBatchPushPacket(bool value) {
        _batchPushPacket = value;
    }
private:
    bool _batchPushPacket;          // ����post packet
};
}

#endif /*ISERVERADAPTER_H*/
