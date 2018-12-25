//
// Created by pczyz on 20.12.18.
//

#ifndef P2P_SENDER_H
#define P2P_SENDER_H


#include "Stoppable.h"
#include "Tasks/Task.h"
#include "Tasks/SenderTasks/SenderTask.h"
#include "Serializers/CommuniqueSerializer.h"
#include <vector>

using namespace std;

class Sender: public Stoppable {
public:
    Sender(vector<SenderTask*>* senderTasks, int socketDescriptor);
    void run();
private:
    int socketDescriptor;
    vector<SenderTask*>* senderTasks;
};


#endif //P2P_SENDER_H
