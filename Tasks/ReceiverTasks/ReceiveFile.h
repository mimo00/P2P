//
// Created by pczyz on 29.12.18.
//

#ifndef P2P_RECEIVEFILE_H
#define P2P_RECEIVEFILE_H

#include "../../OperationCode.h"
#include "ReceiverTask.h"
#include <future>

using namespace std;

class ReceiveFile: public ReceiverTask {
public:
    ReceiveFile(int id, promise<FileFragment>* fileFragment);
    void handle(Input* input) override;
private:
    promise<FileFragment>* fileFragment;
};


#endif //P2P_RECEIVEFILE_H
