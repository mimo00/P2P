//
// Created by michal on 19.12.18.
//

#ifndef P2P_REVEIVER_H
#define P2P_REVEIVER_H

#include <vector>
#include "Stoppable.h"
#include "Tasks/SenderTasks/SenderTask.h"
#include "Serializers/ReceiverDeserializer.h"
#include "Tasks/ReceiverTasks/ReceiverTask.h"

using namespace std;

class Receiver: public Stoppable
{
public:
    Receiver(vector<ReceiverTask*>* receiverTasks,vector<SenderTask*>* senderTasks, int socketDescriptor);
    void run();
private:
    int socketDescriptor;
    vector<ReceiverTask*>* receiverTasks;
    vector<SenderTask*>* senderTasks;
    ReceiverDeserializer receiverDeserializer;
    bool canRead();
    bool isRequest(int operationCode);
    void createResponse(int operationCode, int taskId);
    void processRequest();
};

#endif //P2P_REVEIVER_H
