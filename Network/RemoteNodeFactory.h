//
// Created by michal on 09.01.19.
//

#ifndef P2P_REMOTENODEFACTORY_H
#define P2P_REMOTENODEFACTORY_H


#include "RemoteNode.h"

class RemoteNodeFactory {
    static RemoteNode* createRemoteNode(int sockfd, NodeAddr nodeAddr, NetworkManager* networkManager);
};


#endif //P2P_REMOTENODEFACTORY_H
