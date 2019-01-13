//
// Created by michal on 10.01.19.
//

#include "HostConnector.h"
#include "../../Communication/Initializers/SocketInitializer.h"
#include "../../Communication/Pushers/SocketPusher.h"
#include "../Serializers/Serializer.h"
#include "../Deserializers/Deserializer.h"
#include "../../Communication/Pullers/SocketPuller.h"


HostConnector::HostConnector(NodeAddr me) : Connector(me) {}


int HostConnector::startListining() {
    SocketInitializer socketInitializer;
    lisiningDescriptor = socketInitializer.startListining(me);
    return lisiningDescriptor;
}

int HostConnector::initConnectionWithNode(NodeAddr addr) {
    SocketInitializer socketInitializer;
    int connectionDescriptor = socketInitializer.connectWithNode(addr);
    Serializer serializer(new SocketPusher(connectionDescriptor));
    serializer.sendListiningAddress(me);
    return connectionDescriptor;
}

tuple<NodeAddr, int> HostConnector::acceptNode() {
    SocketInitializer socketInitializer;
    int connectionDescriptor = socketInitializer.acceptNode(lisiningDescriptor);
    Deserializer deserializer(new SocketPuller(connectionDescriptor));
    NodeAddr nodeAddr = deserializer.receiveListiningAddress();
    return make_tuple(nodeAddr, connectionDescriptor);
}

HostConnector::~HostConnector() {
    close(lisiningDescriptor);
}
