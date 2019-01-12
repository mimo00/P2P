//
// Created by pczyz on 28.12.18.
//

#include "ReceiveNodesList.h"
#include "../../Communication/Pullers/SocketPuller.h"
#include "../../Serializers/Deserializers/Deserializer.h"
#include <iostream>

ReceiveNodesList::ReceiveNodesList(int taskId, promise<vector<NodeAddr>> *nodeAddr)
: ReceiverTask(taskId), nodeAddr(nodeAddr){}


void ReceiveNodesList::handle(Input* input) {
    vector<NodeAddr> nodes = input->receiveNodeList();
    nodeAddr->set_value(nodes);
}
