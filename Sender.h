//
// Created by pczyz on 20.12.18.
//

#ifndef P2P_SENDER_H
#define P2P_SENDER_H


#include "Stoppable.h"
#include <vector>
#include "Tasks/Task.h"

using namespace std;

class Sender: public Stoppable {
public:
    Sender(vector<Task>* senderTasks);
    void run();
private:
    vector<Task>* senderTasks;
};


#endif //P2P_SENDER_H
