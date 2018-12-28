//
// Created by pczyz on 28.12.18.
//

#include "NodeListDeserializer.h"
#include "../Communication/Server.h"

NodeListDeserializer::NodeListDeserializer(int socketDescriptor): socketDescriptor(socketDescriptor) {}

vector<NodeAddr> NodeListDeserializer::receive(){
    Server server(socketDescriptor);
    int numberOfAddr = server.readInteger();
    vector<NodeAddr> nodeAddresses = server.receiveNodeAddr(numberOfAddr);
    return nodeAddresses;
}