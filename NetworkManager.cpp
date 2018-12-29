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

int NetworkManager::connectToNetwork(NodeAddr addr) {
    int sockDescriptor;
    if((sockDescriptor = Client::connectWithHost(addr))>=0){
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
