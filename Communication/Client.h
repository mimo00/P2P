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
    void sendInteger(int operationCode);
    void sendFilesNames(vector<File> files);
private:
    int socketDescriptor;
};


#endif //P2P_CLIENT_H
