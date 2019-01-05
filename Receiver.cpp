//
// Created by michal on 19.12.18.
//

#include "Receiver.h"
#include "Serializers/CommuniqueSerializer.h"
#include "OperationCode.h"
#include "Tasks/SenderTasks/SendFilesList.h"
#include "Tasks/SenderTasks/SendNodesList.h"
#include "Tasks/SenderTasks/SendFile.h"
#include "Tasks/SenderTasks/SendResponse.h"
#include <unistd.h>
#include <algorithm>
#include "RemoteNode.h"
#include "NetworkManager.h"

using namespace std;


Receiver::Receiver(RemoteNode* remoteNode): remoteNode(remoteNode) {};


bool Receiver::canRead(){
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(remoteNode->getSockfd(), &rfds);
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    int retval = select(remoteNode->getSockfd()+1, &rfds, NULL, NULL, &tv);
    if (retval == -1)
        perror("select()");
    return retval != 0;
}

void Receiver::createResponse(int operationCode, int taskId){
    /*Funkcja powinna stworzyć odpowiedni Task dla sendera */
    cout<<"Tworze odpowiedz" << endl;
    SenderTask* senderTask;
    switch (operationCode) {
        case OperationCode::FILES_LIST_REQUEST:
            senderTask = new SendFilesList(taskId);
            break;
        case OperationCode::NODES_LIST_REQUEST:
            senderTask = new SendNodesList(taskId, remoteNode->getNetworkManager()->getNodeAddress());
            break;
        case OperationCode::FILE_FRAGMENT_REQUEST:
            ReceiverDeserializer receiverDeserializer(remoteNode->getSockfd());
            auto data=receiverDeserializer.readData();
            int offset=get<0>(data);
            int hash=get<1>(data);
            senderTask = new SendFile(taskId,hash,offset);
            break;
    }
    remoteNode->getSenderTasks()->emplace_back(senderTask);
}

void Receiver::processRequest(int taskId){
    /*Funkcja znajduje Taks o podanym id i odpala go*/
    cout<<"Przetwarzam request" << endl;
    auto receiverTasks = remoteNode->getReceiverTasks();
    auto it = find_if(receiverTasks->begin(), receiverTasks->end(), [&taskId](const ReceiverTask* obj) {return obj->getId() == taskId;});
    if (it != receiverTasks->end())
        (*it)->handle(remoteNode->getSockfd());
    else
        cout<<"Jest bardzo zle !!! Odebralismy nieznany task nalezy wyrejestrowac noda" << endl;
}

void Receiver::run()
{
    ReceiverDeserializer receiverDeserializer(remoteNode->getSockfd());
    while (!stopRequested())
    {
        if (canRead()) {
            try{
                auto data = receiverDeserializer.readData();
                int operationCode = get<0>(data);
                int taskId = get<1>(data);
                cout<<"Odebralem request: " << operationCode << " " << taskId << endl;
                if (OperationCode::isRequest(operationCode))
                    createResponse(operationCode, taskId);
                else
                    processRequest(taskId);
            }catch (ReceiverDeserializerException& e){
                cout<<"Node zerwal polaczenie, wyrejectrowuje noda." << endl;
                remoteNode->getNetworkManager()->unregisterRemoteNode(remoteNode);
            }
        }
        sleep(1);
    }
}