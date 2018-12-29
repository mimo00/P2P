//
// Created by michal on 18.12.18.
//

#ifndef P2P_NETWORKMANAGER_H
#define P2P_NETWORKMANAGER_H


#include <list>
#include <set>
#include "RemoteNode.h"
#include "NetworkData.h"

using  namespace std;

class NetworkManager {
private:
    list<RemoteNode*> remoteNodes;
    NetworkData networkData;
public:
    NetworkData &getNetworkData();

public:
    NetworkManager();
    void registerRemoteNode(RemoteNode* remoteNode);
    void unregisterRemoteNode(RemoteNode* remoteNode);
    int connectToNetwork(NodeAddr addr);
};


#endif //P2P_NETWORKMANAGER_H
