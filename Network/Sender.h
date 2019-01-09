//
// Created by pczyz on 20.12.18.
//

#ifndef P2P_SENDER_H
#define P2P_SENDER_H


#include "Stoppable.h"
#include "../Tasks/SenderTasks/SenderTask.h"
#include <vector>

using namespace std;

class RemoteNode;

class Sender: public Stoppable {
public:
    Sender(RemoteNode* remoteNode);
    void run();
private:
    RemoteNode* remoteNode;
};


#endif //P2P_SENDER_H
