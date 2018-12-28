//
// Created by pczyz on 20.12.18.
//

#include "Sender.h"
#include "Tasks/SenderTasks/SenderTask.h"
#include "Serializers/CommuniqueSerializer.h"

using namespace std;

Sender::Sender(vector<SenderTask*>* senderTasks, int socketDescriptor)
: senderTasks(senderTasks), socketDescriptor(socketDescriptor) {};

void Sender::run() {
//    cout<<"sender started"<<endl;
    while(!stopRequested())
    {
        if (!senderTasks->empty()){
            SenderTask* senderTask = senderTasks->back();
            senderTasks->pop_back();
            senderTask->send(socketDescriptor);
            delete senderTask;
        } else {
//            cout << "Pusty wektor nie biorę nic" << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
}