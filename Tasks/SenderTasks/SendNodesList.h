//
// Created by pczyz on 28.12.18.
//

#ifndef P2P_SENDNODESLIST_H
#define P2P_SENDNODESLIST_H

#include <vector>
#include "SenderTask.h"
#include "../../OperationCode.h"

using namespace std;
class SendNodesList: public SenderTask{
public:
    const int operationCode = OperationCode::NODES_LIST;
    SendNodesList(int id): SenderTask(id){};
    void send(int) override;
private:
    vector<NodeAddr> getNodeAddresses();
};


#endif //P2P_SENDNODESLIST_H
