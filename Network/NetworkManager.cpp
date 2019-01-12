//
// Created by michal on 18.12.18.
//
#include "NetworkManager.h"
#include "RemoteNode.h"
#include "../Communication/Client.h"
#include "FileDownloadManager.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


NetworkManager::NetworkManager(Connector* connector, RemoteNodeFactory* remoteNodeFactory, FileManager* fileManager)
: connector(connector), remoteNodeFactory(remoteNodeFactory), fileManager(fileManager) {}

void NetworkManager::registerRemoteNode(RemoteNode* remoteNode){
    cout<<"Rejestruje !!!"<<endl;
    remoteNodes.push_back(remoteNode);
}

void NetworkManager::unregisterRemoteNode(RemoteNode* remoteNode){
    auto foundRemoteNode = find(remoteNodes.begin(), remoteNodes.end(), remoteNode);
    if(foundRemoteNode == remoteNodes.end())
        throw invalid_argument("Non existing remote node.");
    delete remoteNode;
    remoteNodes.erase(foundRemoteNode);
}


vector<NodeAddr> NetworkManager::getNodeAddress() {
    vector<NodeAddr> nodeAddress;
    for (int i=0;i<remoteNodes.size();i++){
        nodeAddress.push_back(remoteNodes[i]->getNodeAddr());
    }
    return nodeAddress;
}


void NetworkManager::connectToNetwork(NodeAddr addr) {
    int connectionDescription = connector->initConnectionWithNode(addr);
    auto remoteNode = remoteNodeFactory->createRemoteNode(connectionDescription, addr, this);
    registerRemoteNode(remoteNode);
    vector<NodeAddr> addresses = remoteNode->getNodeAddress();
    for(int i=0;i<addresses.size();i++){
        if (addresses[i] != connector->getMe()){
            connectionDescription = connector->initConnectionWithNode(addresses[i]);
            remoteNode = remoteNodeFactory->createRemoteNode(connectionDescription, addresses[i], this);
            registerRemoteNode(remoteNode);
        }
    }
}


vector<File> NetworkManager::getFiles() {
    vector<promise<vector<File>>*> promises(this->remoteNodes.size());
    int i = 0;
    for(int j=0;j<remoteNodes.size();j++) {
        promises[i] = new promise<vector<File>>;
        remoteNodes[i]->getFilesList(promises[i]);
        i++;
    }
    vector<File> files;
    for (int i=0;i<promises.size(); i++){
        future<vector<File>> fileNamesFuture = promises[i]->get_future();
        vector<File> node_files = fileNamesFuture.get();
        files.insert(files.end(), node_files.begin(), node_files.end());
    }
return files;
}

void NetworkManager::fileDownloadManage(File filee) {
    cout << "Pobieram plik " << filee.name << endl;
    auto downloadManager = new FileDownloadManager(filee, remoteNodes[0], fileManager);
    thread downloadThread([&](){downloadManager->Download();});
    downloadThread.detach();
}

NetworkManager::~NetworkManager() {
    for(int i=0;i<remoteNodes.size();i++)
        delete remoteNodes[i];
}

RemoteNodeFactory *NetworkManager::getRemoteNodeFactory() const {
    return remoteNodeFactory;
}

Connector *NetworkManager::getConnector() const {
    return connector;
}

FileManager *NetworkManager::getFileManager() const {
    return fileManager;
}
