//
// Created by pczyz on 28.12.18.
//

#ifndef P2P_NODESLISTSERIALIZER_H
#define P2P_NODESLISTSERIALIZER_H

#include "../OperationCode.h"
#include <vector>

using namespace std;

class NodesListSerializer {
public:
    NodesListSerializer(int socketDescriptor, int operationCode, int taskId,vector<NodeAddr> addresses);
    void send();
private:
    int socketDescriptor;
    int operationCode;
    int taskId;
    vector<NodeAddr> addresses;
};


#endif //P2P_NODESLISTSERIALIZER_H
