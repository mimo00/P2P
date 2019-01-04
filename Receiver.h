//
// Created by michal on 19.12.18.
//

#ifndef P2P_REVEIVER_H
#define P2P_REVEIVER_H

#include <vector>
#include "Stoppable.h"
#include "Tasks/SenderTasks/SenderTask.h"
#include "Serializers/ReceiverDeserializer.h"
#include "Tasks/ReceiverTasks/ReceiverTask.h"

using namespace std;

class RemoteNode;

class Receiver: public Stoppable
{
public:
    Receiver(RemoteNode* remoteNode);
    void run();
private:
    RemoteNode* remoteNode;
    bool canRead();
    void createResponse(int operationCode, int taskId);
    void processRequest(int taskId);
};

#endif //P2P_REVEIVER_H
