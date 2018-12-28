//
// Created by michal on 27.12.18.
//

#ifndef P2P_RECEIVEFILELIST_H
#define P2P_RECEIVEFILELIST_H


#include "ReceiverTask.h"

class ReceiveFileList : public ReceiverTask{
public:
    ReceiveFileList(int id): ReceiverTask(id){};
    void handle(int socket) override;
};


#endif //P2P_RECEIVEFILELIST_H
