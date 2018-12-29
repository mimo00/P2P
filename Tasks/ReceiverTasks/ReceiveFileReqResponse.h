//
// Created by pczyz on 29.12.18.
//

#ifndef P2P_RECEIVEFILEREQRESPONSE_H
#define P2P_RECEIVEFILEREQRESPONSE_H

#include "ReceiverTask.h"
#include "../../OperationCode.h"

#include <future>

using namespace std;
class ReceiveFileReqResponse: public ReceiverTask {
public:
    ReceiveFileReqResponse(int id): ReceiverTask(id){};
    void handle(int socket) override;
private:
    promise<?> cos;

};


#endif //P2P_RECEIVEFILEREQRESPONSE_H
