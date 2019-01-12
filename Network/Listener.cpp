//
// Created by michal on 28.12.18.
//

#include "Listener.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../Communication/Server.h"
#include "../Serializers/Deserializers/Deserializer.h"
#include "../Communication/Pullers/SocketPuller.h"

using namespace std;


Listener::Listener(NetworkManager* networkManager) : networkManager(networkManager) {
    networkManager->getConnector()->startListining();
}

Listener::~Listener() {
}


void Listener::run() {
    while (!stopRequested()) {
        int connectionDescriptor = networkManager->getConnector()->acceptNode();
        SocketPuller socketPuller(connectionDescriptor);
        Deserializer deserializer(&socketPuller);
        NodeAddr nodeAddr = deserializer.receiveListiningAddress();
        RemoteNode* remoteNode = networkManager->getRemoteNodeFactory()->createRemoteNode(connectionDescriptor, nodeAddr, networkManager);
        networkManager->registerRemoteNode(remoteNode);
    }
}

