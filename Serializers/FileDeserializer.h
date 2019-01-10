//
// Created by pczyz on 29.12.18.
//

#ifndef P2P_FILEDESERIALIZER_H
#define P2P_FILEDESERIALIZER_H

//#include <bits/sigcontext.h>
#include "../OperationCode.h"


class FileDeserializer {
public:
    FileDeserializer(int socketDescriptor);
    size_t receiveFileSize();
    void receive(unsigned char* buff, int nread);
private:
    int socketDescriptor;
};


#endif //P2P_FILEDESERIALIZER_H
