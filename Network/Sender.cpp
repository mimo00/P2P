//
// Created by pczyz on 20.12.18.
//

#include "Sender.h"
#include "../Tasks/SenderTasks/SenderTask.h"
#include "RemoteNode.h"

using namespace std;

Sender::Sender(RemoteNode* remoteNode, Output* output)
: remoteNode(remoteNode), output(output) {};


void Sender::run() {
    while(!stopRequested())
    {
        auto senderTasks = remoteNode->getSenderTasks();
        if (!senderTasks->empty()){
            SenderTask* senderTask = senderTasks->back();
            senderTasks->pop_back();
            senderTask->send(output);
            delete senderTask;
        }
    }
}

Sender::~Sender() {
    delete output;
}
