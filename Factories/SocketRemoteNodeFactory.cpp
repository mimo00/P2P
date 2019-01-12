//
// Created by michal on 10.01.19.
//

#include "SocketRemoteNodeFactory.h"
#include "../Communication/Pullers/SocketPuller.h"
#include "../Communication/Pushers/SocketPusher.h"
#include "../Serializers/Serializers/Serializer.h"
#include "../Serializers/Deserializers/Deserializer.h"
#include "../Network/NetworkManager.h"


RemoteNode *SocketRemoteNodeFactory::createRemoteNode(int connectionDescriptor, NodeAddr nodeAddr, NetworkManager *networkManager) {
    auto socketPuller = new SocketPuller(connectionDescriptor);
    auto socketPusher = new SocketPusher(connectionDescriptor);
    auto serializer = new Serializer(socketPusher);
    auto deserializer = new Deserializer(socketPuller);
    auto remoteNode = new RemoteNode(nodeAddr, networkManager);
    auto receiver = new Receiver(remoteNode, deserializer, networkManager->getFileManager());
    auto sender = new Sender(remoteNode, serializer);
    remoteNode->setSenderAndReceiver(receiver, sender);
    return remoteNode;
}
