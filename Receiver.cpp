//
// Created by michal on 19.12.18.
//

#include "Receiver.h"
#include "Serializers/CommuniqueSerializer.h"
#include "OperationCode.h"
#include "Tasks/SenderTasks/SendFilesList.h"
#include <unistd.h>
#include <list>
#include <algorithm>

using namespace std;

Receiver::Receiver(vector<Task*>* receiverTasks,vector<SenderTask*>* senderTask, int socketDescriptor)
: receiverTasks(receiverTasks), senderTasks(senderTask), socketDescriptor(socketDescriptor), receiverDeserializer(socketDescriptor) {};


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

bool Receiver::isRequest(int operationCode){
    const list<int> requestOperationCodes = list<int>({OperationCode::FILES_LIST_REQUEST});
    return find(requestOperationCodes.begin(), requestOperationCodes.end(), operationCode) != requestOperationCodes.end();
}

void Receiver::createResponse(int operationCode, int taskId){
    /*Funkcja powinna stworzyć odpowiedni Task dla sendera */
    cout<<"Tworze odpowiedz" << endl;
    SenderTask* senderTask;
    switch (operationCode)
    {
        case OperationCode::FILES_LIST_REQUEST:
            senderTask = new SendFilesList(taskId);
            senderTasks->emplace_back(senderTask);
            break;
    }
}

void Receiver::processRequest(){
    cout<<"Przetwarzam request" << endl;
}

void Receiver::run()
{
    while (!stopRequested())
    {
        if (canRead()) {
            try{
                auto data = receiverDeserializer.readData();
                int operationCode = get<0>(data);
                int taskId = get<0>(data);
                if (isRequest(operationCode))
                    createResponse(operationCode, taskId);
                else
                    processRequest();
            }catch (BrokenConnectionException& e){
                //Wyrejestrowanie noda
            }
        }
        sleep(1);
    }
}