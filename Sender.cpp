//
// Created by pczyz on 20.12.18.
//

#include "Sender.h"
#include "Tasks/SenderTask.h"
#include "Serializers/SenderSerializer.h"

using namespace std;

Sender::Sender(vector<SenderTask*>* senderTasks, int socketDescriptor)
: senderTasks(senderTasks), socketDescriptor(socketDescriptor), senderSerializer(socketDescriptor) {};

void Sender::run() {
//    cout<<"sender started"<<endl;
    while(!stopRequested())
    {
        if (!senderTasks->empty()){
            SenderTask* senderTask = senderTasks->back();
            senderTasks->pop_back();
            Package package = senderTask->getPackage();
            senderSerializer.send(package);
        } else {
//            cout << "Pusty wektor nie biorę nic" << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
//    cout<<"sender ended";
}