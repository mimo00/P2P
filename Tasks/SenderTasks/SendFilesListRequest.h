//
// Created by michal on 21.12.18.
//

#ifndef P2P_SENDFILESLIST_H
#define P2P_SENDFILESLIST_H


#include "../Task.h"
#include "SenderTask.h"
#include "../../OperationCode.h"

class SendFilesListRequest: public SenderTask {
public:
    const int operatinoCode = OperationCode::FILES_LIST_REQUEST;
    SendFilesListRequest(int id): SenderTask(id){};
    void send(int) override;
};


#endif //P2P_SENDFILESLIST_H
