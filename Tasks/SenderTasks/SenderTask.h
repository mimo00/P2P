//
// Created by michal on 21.12.18.
//

#ifndef P2P_SENDERTASK_H
#define P2P_SENDERTASK_H


#include "../Task.h"
#include "../../Packages/Package.h"

class SenderTask {
public:
    SenderTask(int id): id(id){};
    virtual void send(int) = 0;
protected:
    int id;
};


#endif //P2P_SENDERTASK_H
