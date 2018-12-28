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
    ReceiveNodesList(int id, promise<vector<NodeAddr>>* nodeAddr): ReceiverTask(id), nodeAddr(nodeAddr){};
    void handle(int socket) override;
private:
    promise<vector<NodeAddr>>* nodeAddr;
};


#endif //P2P_RECEIVENODESLIST_H
