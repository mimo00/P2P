//
// Created by michal on 19.12.18.
//

#include "Receiver.h"
#include "Serializers/SenderSerializer.h"
#include "Packages/ListOfFilesPackage.h"
#include <unistd.h>

using namespace std;

Receiver::Receiver(vector<Task*>* receiverTasks,vector<SenderTask*>* senderTask, int socketDescriptor)
: receiverTasks(receiverTasks), senderTask(senderTask), socketDescriptor(socketDescriptor), receiverDeserializer(socketDescriptor) {};


bool Receiver::canRead(){
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(socketDescriptor, &rfds);
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    int retval = select(socketDescriptor+1, &rfds, NULL, NULL, &tv);
    if (retval == -1)
        perror("select()");
    return retval != 0;
}


void Receiver::run()
{
    while (!stopRequested())
    {
        if (canRead()) {
            receiverDeserializer.readData();
        }
        sleep(1);
    }
}