//
// Created by pczyz on 29.12.18.
//

#ifndef P2P_RECEIVEFILE_H
#define P2P_RECEIVEFILE_H

#include "../../OperationCode.h"
#include "ReceiverTask.h"
#include <future>

using namespace std;

class ReceiveFileFragment: public ReceiverTask {
public:
    ReceiveFileFragment(int id, promise<FileFragment>* fileFragment);
    void handle(int operationCode, Input* input) override;
    void close() override;

private:
    promise<FileFragment>* fileFragment;
};


#endif //P2P_RECEIVEFILE_H
