//
// Created by michal on 18.12.18.
//

#ifndef P2P_NETWORKMANAGER_H
#define P2P_NETWORKMANAGER_H


#include <list>
#include <set>
#include "RemoteNode.h"
#include "FileDownloadManager.h"

using  namespace std;

class NetworkManager {
private:
    vector<RemoteNode*> remoteNodes;
    NodeAddr me;
    vector<NodeAddr> nodeAddress;
    int initConnect(NodeAddr addr, NodeAddr me);
    int connect(NodeAddr addr, NodeAddr me);
    FileDownloadManager *downloadManager = nullptr;
public:
    NetworkManager(NodeAddr me);
    virtual ~NetworkManager();
    const vector<NodeAddr> &getNodeAddress() const;

public:
    void registerRemoteNode(RemoteNode* remoteNode);
    void unregisterRemoteNode(RemoteNode* remoteNode);
    int connectToNetwork(NodeAddr addr, NodeAddr me);
    void addNodeAddress(NodeAddr nodeAddr);
    void removeNodeAddress(NodeAddr nodeAddr);
    vector<File> getFiles();
    void fileDownloadManage(File file);
};


#endif //P2P_NETWORKMANAGER_H
