//
// Created by michal on 29.12.18.
//

#ifndef P2P_NETWORKDATA_H
#define P2P_NETWORKDATA_H


#include <vector>
#include "OperationCode.h"

using namespace std;

class NetworkData {
public:
    NetworkData(NodeAddr me);
    void addNodeAddress(NodeAddr nodeAddr);
    void addNodeAddresses(vector<NodeAddr> nodeAddr);
    const vector<NodeAddr> &getNodeAddress() const;
private:
    NodeAddr me;
    vector<NodeAddr> nodeAddress;
};


#endif //P2P_NETWORKDATA_H
