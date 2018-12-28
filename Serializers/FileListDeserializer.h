//
// Created by michal on 27.12.18.
//

#ifndef P2P_FILELISTDESERIALIZER_H
#define P2P_FILELISTDESERIALIZER_H


#include "../OperationCode.h"
#include <vector>

using namespace std;

class FileListDeserializer {
public:
    FileListDeserializer(int socketDescriptor);
    vector<File> receive();
private:
    int socketDescriptor;
};


#endif //P2P_FILELISTDESERIALIZER_H
