//
// Created by pczyz on 20.12.18.
//

#include "Sender.h"
#include "Tasks/SenderTasks/SenderTask.h"
#include "Serializers/CommuniqueSerializer.h"
#include "RemoteNode.h"

using namespace std;

Sender::Sender(RemoteNode* remoteNode) : remoteNode(remoteNode) {};

void Sender::run() {
    while(!stopRequested())
    {
        auto senderTasks = remoteNode->getSenderTasks();
        if (!senderTasks->empty()){
            SenderTask* senderTask = senderTasks->back();
            senderTasks->pop_back();
            senderTask->send(remoteNode->getSockfd());
            delete senderTask;
        } else {
//            cout << "Pusty wektor nie biorę nic" << endl;
        }
        //this_thread::sleep_for(chrono::milliseconds(2000));
    }
}