//
// Created by pczyz on 28.12.18.
//

#include "SendNodesList.h"
#include "../../Communication/Pushers/SocketPusher.h"
#include "../../Serializers/Serializers/Serializer.h"
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

vector<NodeAddr> SendNodesList::getNodeAddresses() {
    return nodeAddress;
}

SendNodesList::SendNodesList(int id, vector<NodeAddr> nodeAddress)
: SenderTask(id), nodeAddress(nodeAddress){}


void SendNodesList::send(Output* output) {
    output->sendNodesList(taskId, getNodeAddresses());
}