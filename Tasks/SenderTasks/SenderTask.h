//
// Created by michal on 21.12.18.
//

#ifndef P2P_SENDERTASK_H
#define P2P_SENDERTASK_H


#include "../../Serializers/Serializers/Output.h"

class SenderTask {
public:
    SenderTask(int taskId): taskId(taskId){};
    virtual void send(Output* output) = 0;
protected:
    int taskId;
};


#endif //P2P_SENDERTASK_H
