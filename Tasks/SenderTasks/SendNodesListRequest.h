//
// Created by pczyz on 28.12.18.
//

#ifndef P2P_SENDNODESLISTREQUEST_H
#define P2P_SENDNODESLISTREQUEST_H

#include "SenderTask.h"
#include "../../OperationCode.h"

class SendNodesListRequest: public SenderTask {
public:
    const int operationCode = OperationCode::NODES_LIST_REQUEST;
    SendNodesListRequest(int id): SenderTask(id){};
    void send(int) override;

};


#endif //P2P_SENDNODESLISTREQUEST_H
