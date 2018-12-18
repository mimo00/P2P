//
// Created by michal on 18.12.18.
//
#include "NetworkManager.h"
#include "RemoteNode.h"
#include <algorithm>

using namespace std;

void NetworkManager::registerRemoteNode(RemoteNode remoteNode){
    remoteNodes.push_back(remoteNode);
}

void NetworkManager::unregisterRemoteNode(RemoteNode remoteNode){
    this->remoteNodes.erase(remove(this->remoteNodes.begin(), this->remoteNodes.end(), remoteNode), this->remoteNodes.end());
}


set<string> NetworkManager::getFiles(){
    set<string> files;
    for (auto remote_node : this->remoteNodes){
        vector<string> node_files = remote_node.get_files();
        for (auto file : node_files){
            files.insert(file);
        }
    }
    return files;
}