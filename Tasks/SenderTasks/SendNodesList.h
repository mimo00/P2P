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
    SendNodesList(int id, vector<NodeAddr> nodeAddress);
    void send(Output* output) override;
private:
    vector<NodeAddr> getNodeAddresses();
    vector<NodeAddr> nodeAddress;
};


#endif //P2P_SENDNODESLIST_H
