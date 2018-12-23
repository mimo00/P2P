//
// Created by michal on 19.12.18.
//

#ifndef P2P_REVEIVER_H
#define P2P_REVEIVER_H

#include <vector>
#include "Stoppable.h"
#include "Tasks/Task.h"
#include "Tasks/SenderTasks/SenderTask.h"
#include "Serializers/ReceiverDeserializer.h"

using namespace std;

class Receiver: public Stoppable
{
public:
    Receiver(vector<Task*>* receiverTasks,vector<SenderTask*>* senderTasks, int socketDescriptor);
    void run();
private:
    int socketDescriptor;
    vector<Task*>* receiverTasks;
    vector<SenderTask*>* senderTasks;
    ReceiverDeserializer receiverDeserializer;
    bool canRead();
    bool isRequest(Package&);
    void createResponse(Package&);
    void processRequest(Package&);
};

#endif //P2P_REVEIVER_H
