//
// Created by pczyz on 28.12.18.
//

#ifndef P2P_NODELISTDESERIALIZER_H
#define P2P_NODELISTDESERIALIZER_H

#include "../OperationCode.h"
#include <vector>

using namespace std;

class NodeListDeserializer {
public:
    NodeListDeserializer(int socketDescriptor);
    vector<NodeAddr> receive();
private:
    int socketDescriptor;
};


#endif //P2P_NODELISTDESERIALIZER_H
