//
// Created by michal on 27.12.18.
//

#ifndef P2P_RECEIVERTASK_H
#define P2P_RECEIVERTASK_H


#include "../../Serializers/Deserializers/Input.h"

class ReceiverTask {
public:
    ReceiverTask(int taskId);
    virtual void handle(int operationCode, Input* input) = 0;
    virtual void close() = 0;
    int getTaskId() const;
    //virtual ~ReceiverTask(){}
protected:
    int taskId;
    Input* input;
};

#endif //P2P_RECEIVERTASK_H
