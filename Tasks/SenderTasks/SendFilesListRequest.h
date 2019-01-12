//
// Created by michal on 21.12.18.
//

#ifndef P2P_SENDFILESLIST_H
#define P2P_SENDFILESLIST_H


#include "SenderTask.h"
#include "../../OperationCode.h"

class SendFilesListRequest: public SenderTask {
public:
    SendFilesListRequest(int taskId);
    void send(Output* output) override;
};


#endif //P2P_SENDFILESLIST_H
