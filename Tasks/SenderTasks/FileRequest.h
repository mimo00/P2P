//
// Created by pczyz on 29.12.18.
//

#ifndef P2P_FILEREQUEST_H
#define P2P_FILEREQUEST_H

#include "SenderTask.h"
#include "../../OperationCode.h"

class FileRequest: public SenderTask{
public:
    FileRequest(int taskId, int hash, int offset);
    void send(Output* output) override;
private:
    int offset;
    int hash;
};


#endif //P2P_FILEREQUEST_H
