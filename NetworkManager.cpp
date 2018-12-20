//
// Created by michal on 18.12.18.
//
#include "NetworkManager.h"
#include "RemoteNode.h"
#include <algorithm>
#include <stdexcept>

using namespace std;


NetworkManager::NetworkManager(){}

void NetworkManager::registerRemoteNode(int sockfd){
    remoteNodes.emplace_back(sockfd);
}

void NetworkManager::unregisterRemoteNode(int sockfd){
    auto it = find_if(remoteNodes.begin(), remoteNodes.end(), [&sockfd](const RemoteNode& obj) {return obj.getSockfd() == sockfd;});
    if(it == remoteNodes.end())
        throw invalid_argument("Non existing socket.");
    it->receiver->stop();
    remoteNodes.erase(remove_if(begin(remoteNodes), end(remoteNodes), [sockfd](RemoteNode const& u)
    {
        return u.getSockfd() == sockfd;
    }), end(remoteNodes));
    cout<<remoteNodes.size()<<endl;
}
