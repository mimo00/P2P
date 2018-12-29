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
    SendFile(int id): SenderTask(id){};
    void send(int) override;
private:
    FileFragment fileFragment;
};


#endif //P2P_SENDFILE_H
