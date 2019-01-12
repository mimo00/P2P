//
// Created by michal on 19.12.18.
//

#ifndef P2P_REVEIVER_H
#define P2P_REVEIVER_H

#include <vector>
#include "Stoppable.h"
#include "../Tasks/SenderTasks/SenderTask.h"
#include "../Tasks/ReceiverTasks/ReceiverTask.h"
#include "../FileManager.h"

using namespace std;

class RemoteNode;

class Receiver: public Stoppable
{
public:
    Receiver(RemoteNode* remoteNode, Input* input, FileManager* fileManager);
    void run() override;
private:
    RemoteNode* remoteNode;
    Input* input;
    FileManager* fileManager;
    void createResponse(int operationCode, int taskId);
    void processRequest(int operationCode, int taskId);
};

#endif //P2P_REVEIVER_H
