//
// Created by michal on 18.12.18.
//

#ifndef P2P_NETWORKMANAGER_H
#define P2P_NETWORKMANAGER_H


#include <vector>
#include <set>
#include "RemoteNode.h"

using  namespace std;

class NetworkManager {
private:
    vector<RemoteNode> remoteNodes;
public:
    set<string> getFiles();
    void registerRemoteNode(RemoteNode remoteNode);
    void unregisterRemoteNode(RemoteNode remoteNode);
};


#endif //P2P_NETWORKMANAGER_H
