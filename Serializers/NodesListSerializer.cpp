//
// Created by pczyz on 28.12.18.
//

#include "NodesListSerializer.h"
#include "../Communication/Client.h"

NodesListSerializer::NodesListSerializer(int socketDescriptor, int operationCode, int taskId,vector<NodeAddr> addresses)
: socketDescriptor(socketDescriptor), operationCode(operationCode),taskId(taskId),addresses(addresses) {}

void NodesListSerializer::send() {
    Client client(socketDescriptor);
    int numberOfNodes = static_cast<int>(addresses.size());
    client.sendInteger(operationCode);
    client.sendInteger(taskId);
    client.sendInteger(numberOfNodes);
    client.sendNodeAddr(addresses);
};