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
    vector<NodeAddr> addresses;
    NodeAddr nodeAddr;
    //TODO: dodać logikę pobierania listy nodes
    nodeAddr.addr.s_addr = inet_addr("127.0.0.1");
    nodeAddr.port = htons(3000);

    addresses.push_back(nodeAddr);

    return addresses;
}

void SendNodesList::send(int socket) {
    NodesListSerializer nodesListSerializer(socket,operationCode,id,getNodeAddresses());
    nodesListSerializer.send();
}