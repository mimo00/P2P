//
// Created by michal on 22.12.18.
//

#ifndef P2P_CLIENT_H
#define P2P_CLIENT_H

#include <vector>
#include "../OperationCode.h"

using namespace std;

class Client {
public:
    Client(int);
    static int connectWithHost(NodeAddr addr);
    void sendInteger(int operationCode);
    void sendFilesNames(vector<File> files);
    void sendNodeAddr(vector<NodeAddr> nodeAddr);
private:
    int socketDescriptor;
};


#endif //P2P_CLIENT_H
