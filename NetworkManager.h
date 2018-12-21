//
// Created by michal on 18.12.18.
//

#ifndef P2P_NETWORKMANAGER_H
#define P2P_NETWORKMANAGER_H


#include <list>
#include <set>
#include "RemoteNode.h"

using  namespace std;

class NetworkManager {
private:
    list<RemoteNode*> remoteNodes;
public:
    NetworkManager();
    void registerRemoteNode(RemoteNode* remoteNode);
    void unregisterRemoteNode(RemoteNode* remoteNode);
};


#endif //P2P_NETWORKMANAGER_H
