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
    SocketPusher socketPusher(connectionDescriptor);
    Serializer serializer(&socketPusher);
    serializer.sendListiningAddress(me);
    return connectionDescriptor;
}

int HostConnector::acceptNode() {
    SocketInitializer socketInitializer;
    int connectionDescriptor = socketInitializer.acceptNode(lisiningDescriptor);
    return connectionDescriptor;
}
