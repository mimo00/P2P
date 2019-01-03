//
// Created by pczyz on 30.12.18.
//

#ifndef P2P_SENDRESPONSE_H
#define P2P_SENDRESPONSE_H

#include "SenderTask.h"
#include "../../OperationCode.h"

using namespace std;

class SendResponse: public SenderTask {
public:
    const int operationCode;
    SendResponse(int id,int operationCode): SenderTask(id), operationCode(operationCode){};
    void send(int) override;
};


#endif //P2P_SENDRESPONSE_H
