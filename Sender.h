//
// Created by pczyz on 20.12.18.
//

#ifndef P2P_SENDER_H
#define P2P_SENDER_H


#include "Stoppable.h"
#include "Tasks/Task.h"
#include "Tasks/SenderTask.h"
#include "Serializers/SenderSerializer.h"
#include <vector>

using namespace std;

class Sender: public Stoppable {
public:
    Sender(vector<SenderTask*>* senderTasks);
    void run();
private:
    SenderSerializer requestSerializer;
    vector<SenderTask*>* senderTasks;
};


#endif //P2P_SENDER_H
