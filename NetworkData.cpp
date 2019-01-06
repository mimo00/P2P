//
// Created by michal on 29.12.18.
//

#include <iostream>
#include "NetworkData.h"


NetworkData::NetworkData(NodeAddr me): me(me) {}

void NetworkData::addNodeAddress(NodeAddr nodeAddr) {
    //nodeAddress.push_back(nodeAddr);
}

void NetworkData::addNodeAddresses(vector<NodeAddr> nodeAddr) {
    //nodeAddress.insert(nodeAddress.end(), nodeAddr.begin(), nodeAddr.end());
    //nodeAddress.erase(std::remove(nodeAddress.begin(), nodeAddress.end(), me), nodeAddress.end());
}

const vector<NodeAddr> &NetworkData::getNodeAddress() const {
    return nodeAddress;
}



