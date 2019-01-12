//
// Created by michal on 09.01.19.
//

#ifndef P2P_REMOTENODEFACTORY_H
#define P2P_REMOTENODEFACTORY_H


#include "../Network/RemoteNode.h"

class RemoteNodeFactory {
public:
    virtual RemoteNode* createRemoteNode(int connectionDescriptor, NodeAddr nodeAddr, NetworkManager* networkManager)=0;
};


#endif //P2P_REMOTENODEFACTORY_H
