//
// Created by pczyz on 28.12.18.
//

#ifndef P2P_FILESERIALIZER_H
#define P2P_FILESERIALIZER_H

#include "../OperationCode.h"

class FileSerializer {
public:
    FileSerializer(int socketDescriptor, int operationCode, int taskId, int hash,int fileOffset);
    void send();
private:
    int socketDescriptor;
    int operationCode;
    int taskId;
    int hash;
    int fileOffset;
};


#endif //P2P_FILESERIALIZER_H
