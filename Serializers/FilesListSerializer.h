//
// Created by michal on 25.12.18.
//

#ifndef P2P_FILESLISTSERIALIZER_H
#define P2P_FILESLISTSERIALIZER_H


#include "../Packages/Package.h"
#include "../OperationCode.h"
#include <vector>

using namespace std;

class FilesListSerializer {
public:
    FilesListSerializer(int socketDescriptor, int operationCode, int taskId, vector<File> files);
    void send();

private:
    int socketDescriptor;
    int operationCode;
    int taskId;
    vector<File> files;
};


#endif //P2P_FILESLISTSERIALIZER_H
