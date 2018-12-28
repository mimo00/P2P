//
// Created by pczyz on 28.12.18.
//

#include "ReceiveNodesList.h"
#include "../../Serializers/NodeListDeserializer.h"
#include <iostream>

void ReceiveNodesList::handle(int socket) {
    NodeListDeserializer nodeListDeserializer(socket);
    vector<NodeAddr> nodeAddr_ = nodeListDeserializer.receive();
    nodeAddr->set_value(nodeAddr_);
}