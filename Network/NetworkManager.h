//
// Created by michal on 18.12.18.
//

#ifndef P2P_NETWORKMANAGER_H
#define P2P_NETWORKMANAGER_H


#include <list>
#include <set>
#include "RemoteNode.h"
#include "../Serializers/Connectors/Connector.h"
#include "../Factories/RemoteNodeFactory.h"

using  namespace std;

class NetworkManager {
private:
    vector<RemoteNode*> remoteNodes;
    bool doResume(File file);
    Connector* connector = nullptr;
    RemoteNodeFactory* remoteNodeFactory = nullptr;
    FileManager* fileManager = nullptr;
    mutex mutexReg;
public:
    NetworkManager(Connector* connector, RemoteNodeFactory* remoteNodeFactory, FileManager* fileManager);
    virtual ~NetworkManager();
    vector<NodeAddr> getNodeAddress();
    RemoteNodeFactory *getRemoteNodeFactory() const;
    Connector *getConnector() const;
    FileManager *getFileManager() const;
    void resumeDownload(string path);
public:
    void registerRemoteNode(RemoteNode* remoteNode);
    void unregisterRemoteNode(RemoteNode* remoteNode);
    void connectToNetwork(NodeAddr addr);
    vector<File> getFiles();
    void downloadFile(File file);
    FileFragment getFileFragmentFromRemoteNode(File file, int offset);
};

class FileNotAvailableOnNetwork : public exception {};


#endif //P2P_NETWORKMANAGER_H
