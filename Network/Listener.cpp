//
// Created by michal on 28.12.18.
//

#include "Listener.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../Serializers/Deserializers/Deserializer.h"
#include "../Communication/Pullers/SocketPuller.h"

using namespace std;


Listener::Listener(NetworkManager* networkManager) : networkManager(networkManager) {
    networkManager->getConnector()->startListining();
}


void Listener::run() {
    while (!stopRequested()) {
        auto data = networkManager->getConnector()->acceptNode();
        NodeAddr nodeAddr = get<0>(data);
        int connectionDescriptor = get<1>(data);
        RemoteNode* remoteNode = networkManager->getRemoteNodeFactory()->createRemoteNode(connectionDescriptor, nodeAddr, networkManager);
        networkManager->registerRemoteNode(remoteNode);
    }
}

