//
// Created by pczyz on 28.12.18.
//

#include "ReceiveNodesList.h"
#include "../../Communication/Pullers/SocketPuller.h"
#include "../../Serializers/Deserializers/Deserializer.h"
#include <iostream>

void ReceiveNodesList::handle(int socket) {
    SocketPuller puller(socket);
    Deserializer deserializer(&puller);
    vector<NodeAddr> nodes = deserializer.receiveNodeList();
    nodeAddr->set_value(nodes);
}