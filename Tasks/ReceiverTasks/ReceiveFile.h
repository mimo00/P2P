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
    ReceiveFile(int id,File file, int offset, promise<FileFragment>* fileFragment)
    :ReceiverTask(id),file(file),offset(offset),fileFragment(fileFragment){};
    void handle(int socket) override;
private:
    promise<FileFragment>* fileFragment;
    File file;
    int offset;
};


#endif //P2P_RECEIVEFILE_H
