//
// Created by michal on 19.12.18.
//

#ifndef P2P_REVEIVER_H
#define P2P_REVEIVER_H

#include <vector>
#include "Stoppable.h"
#include "../Tasks/SenderTasks/SenderTask.h"
#include "../Tasks/ReceiverTasks/ReceiverTask.h"
#include "../Resources/FileManager.h"

using namespace std;

class RemoteNode;

class Receiver: public Stoppable
{
private:
    RemoteNode* remoteNode;
    Input* input;
    FileManager* fileManager;
    void createResponse(int operationCode, int taskId);
    void processRequest(int operationCode, int taskId);
public:
    Receiver(RemoteNode* remoteNode, Input* input, FileManager* fileManager);
    virtual ~Receiver();
    void run() override;
};

#endif //P2P_REVEIVER_H
