//
// Created by pczyz on 28.12.18.
//

#include "SendNodesList.h"
#include "../../Serializers/CommuniqueSerializer.h"
#include "../../Communication/Pushers/SocketPusher.h"
#include "../../Serializers/Serializers/Serializer.h"
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

vector<NodeAddr> SendNodesList::getNodeAddresses() {
    return nodeAddress;
}

void SendNodesList::send(int socket) {
    SocketPusher socketPusher(socket);
    Serializer serializer(&socketPusher);
    serializer.sendNodesList(id, getNodeAddresses());
}