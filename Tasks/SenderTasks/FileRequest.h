//
// Created by pczyz on 29.12.18.
//

#ifndef P2P_FILEREQUEST_H
#define P2P_FILEREQUEST_H

#include "SenderTask.h"
#include "../../OperationCode.h"

class FileRequest: public SenderTask{
public:
    const int operationCode = OperationCode::FILE_FRAGMENT_REQUEST;
    FileRequest(int id,int offset,int hash): SenderTask(id), offset(offset),hash(hash){};
    void send(int) override;
private:
    int offset;
    int hash;
};


#endif //P2P_FILEREQUEST_H
