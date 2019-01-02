//
// Created by michal on 18.12.18.
//
#include "NetworkManager.h"
#include "RemoteNode.h"
#include "Communication/Client.h"
#include <algorithm>
#include <stdexcept>

using namespace std;


NetworkManager::NetworkManager(){}

void NetworkManager::registerRemoteNode(RemoteNode* remoteNode){
    remoteNodes.emplace_back(remoteNode);
}

void NetworkManager::unregisterRemoteNode(RemoteNode* remoteNode){
    auto foundRemoteNode = find(remoteNodes.begin(), remoteNodes.end(), remoteNode);
    if(foundRemoteNode == remoteNodes.end())
        throw invalid_argument("Non existing remote node.");
    (*foundRemoteNode)->getReceiver()->stop();
    remoteNodes.erase(foundRemoteNode);
}

int NetworkManager::connectToNetwork(NodeAddr addr, NodeAddr me) {
    int sockDescriptor;
    if((sockDescriptor = Client::connectWithHost(addr))>=0){
        Client client(sockDescriptor);
        client.sendInteger(me.port);
        networkData.addNodeAddress(addr);
        auto remoteNode = new RemoteNode(sockDescriptor);
        registerRemoteNode(remoteNode);
        networkData.addNodeAddresses(remoteNode->getNodeAddress());
        return 0;
    } else
        return 1;
}

NetworkData &NetworkManager::getNetworkData() {
    return networkData;
}

vector<File> NetworkManager::getFiles() {
    vector<promise<vector<File>>*> promises(this->remoteNodes.size());
    int i = 0;
    for(auto it=this->remoteNodes.begin(); it != this->remoteNodes.end(); ++it) {
        promises[i] = new promise<vector<File>>;
        (*it)->getFilesList(promises[i]);
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
