//
// Created by michal on 18.12.18.
//

#ifndef P2P_NETWORKMANAGER_H
#define P2P_NETWORKMANAGER_H


#include <list>
#include <set>
#include <mutex>
#include "RemoteNode.h"
#include "../Serializers/Connectors/Connector.h"
#include "../Factories/RemoteNodeFactory.h"

using  namespace std;

class NetworkManager {
private:
    vector<RemoteNode*> remoteNodes;
    Connector* connector;
    RemoteNodeFactory* remoteNodeFactory;
    mutex mutexReg;

public:
    NetworkManager(Connector* connector, RemoteNodeFactory* remoteNodeFactory);
    virtual ~NetworkManager();
    vector<NodeAddr> getNodeAddress();
    RemoteNodeFactory *getRemoteNodeFactory() const;
    Connector *getConnector() const;
public:
    void registerRemoteNode(RemoteNode* remoteNode);
    void unregisterRemoteNode(RemoteNode* remoteNode);
    void connectToNetwork(NodeAddr addr);
    vector<File> getFiles();
    void fileDownloadManage(File file);
};


#endif //P2P_NETWORKMANAGER_H