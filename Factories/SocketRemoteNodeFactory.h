//
// Created by michal on 10.01.19.
//

#ifndef P2P_SOCKETREMOTENODEFACTORY_H
#define P2P_SOCKETREMOTENODEFACTORY_H


#include "RemoteNodeFactory.h"

class SocketRemoteNodeFactory: public RemoteNodeFactory {
public:
    RemoteNode *createRemoteNode(int connectionDescriptor, NodeAddr nodeAddr, NetworkManager *networkManager) override;

};


#endif //P2P_SOCKETREMOTENODEFACTORY_H
