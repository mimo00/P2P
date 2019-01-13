//
// Created by pczyz on 28.12.18.
//

#ifndef P2P_RECEIVENODESLIST_H
#define P2P_RECEIVENODESLIST_H

#include "ReceiverTask.h"
#include "../../OperationCode.h"

#include <future>
#include <vector>

using namespace std;
class ReceiveNodesList:public ReceiverTask {
public:
    ReceiveNodesList(int taskId, promise<vector<NodeAddr>>* nodeAddr);
    void handle(int operationCode, Input* input) override;
    void close() override;

private:
    promise<vector<NodeAddr>>* nodeAddr;
};


#endif //P2P_RECEIVENODESLIST_H
