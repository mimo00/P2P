//
// Created by pczyz on 28.12.18.
//

#include "SendNodesList.h"
#include "../../Serializers/CommuniqueSerializer.h"
#include "../../Serializers/NodesListSerializer.h"
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

vector<NodeAddr> SendNodesList::getNodeAddresses() {
    return nodeAddress;
}

void SendNodesList::send(int socket) {
    NodesListSerializer nodesListSerializer(socket,operationCode,id,getNodeAddresses());
    nodesListSerializer.send();
}