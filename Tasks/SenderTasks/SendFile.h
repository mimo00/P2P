//
// Created by pczyz on 28.12.18.
//

#ifndef P2P_SENDFILE_H
#define P2P_SENDFILE_H

#include "SenderTask.h"
#include "../../OperationCode.h"

class SendFile: public SenderTask {
public:
    const int operationCode = OperationCode::FILE_FRAGMENT;
    SendFile(int id,int hash,int offset): SenderTask(id),hash(hash),offset(offset){};
    void send(int) override;
private:
    int hash;
    int offset;
};


#endif //P2P_SENDFILE_H
