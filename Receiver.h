//
// Created by michal on 19.12.18.
//

#ifndef P2P_REVEIVER_H
#define P2P_REVEIVER_H

#include <vector>
#include "Stoppable.h"
#include "Tasks/Task.h"
#include "Tasks/SenderTask.h"

using namespace std;

class Receiver: public Stoppable
{
public:
    Receiver(vector<Task*>* receiverTasks,vector<SenderTask*>* senderTasks);
    void run();
private:
    vector<Task*>* receiverTasks;
    vector<SenderTask*>* senderTask;
};

#endif //P2P_REVEIVER_H
