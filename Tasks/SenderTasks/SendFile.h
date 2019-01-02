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
    SendFile(int id,int hash,int offset): SenderTask(id),hash(hash),offset(offset){buffer[OperationCode::PORTION]={0};};
    void send(int) override;
private:
    bool isFile(int hash);
    int readyToSend();
    int hash;
    int offset;
    unsigned char buffer[];
};


#endif //P2P_SENDFILE_H
