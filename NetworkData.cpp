//
// Created by michal on 29.12.18.
//

#include <iostream>
#include "NetworkData.h"


NetworkData::NetworkData() {}

void NetworkData::addNodeAddress(NodeAddr nodeAddr) {
    nodeAddress.push_back(nodeAddr);
}

void NetworkData::addNodeAddresses(vector<NodeAddr> nodeAddr) {
    nodeAddress.insert(nodeAddress.end(), nodeAddr.begin(), nodeAddr.end());
}


int NetworkData::getLiczbe() {
    return 666;
}

const vector<NodeAddr> &NetworkData::getNodeAddress() const {
    return nodeAddress;
}



