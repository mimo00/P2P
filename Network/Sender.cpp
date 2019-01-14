//
// Created by pczyz on 20.12.18.
//

#include "Sender.h"
#include "../Tasks/SenderTasks/SenderTask.h"
#include "RemoteNode.h"
#include "NetworkManager.h"

using namespace std;

Sender::Sender(RemoteNode* remoteNode, Output* output)
: remoteNode(remoteNode), output(output) {};


void Sender::run() {
    while(!stopRequested())
    {
        auto senderTask = remoteNode->popSenderTask();
        if (senderTask != nullptr){
            try{
                senderTask->send(output);
                delete senderTask;
            }catch (EndOfDataException& e) {
                remoteNode->getNetworkManager()->unregisterRemoteNode(remoteNode);
                return;
            }
        }
    }
}

Sender::~Sender() {
    delete output;
}
