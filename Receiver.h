//
// Created by michal on 19.12.18.
//

#ifndef P2P_REVEIVER_H
#define P2P_REVEIVER_H

#include <vector>
#include "Stoppable.h"
#include "Tasks/Task.h"

using namespace std;

class Receiver: public Stoppable
{
public:
    Receiver(vector<Task>* receiverTasks,vector<Task>* senderTasks);
    void run();
private:
    vector<Task>* receiverTasks;
    vector<Task>* senderTasks;
};

#endif //P2P_REVEIVER_H
