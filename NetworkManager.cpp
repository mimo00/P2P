//
// Created by michal on 18.12.18.
//
#include "NetworkManager.h"
#include "RemoteNode.h"
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
