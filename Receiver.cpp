//
// Created by michal on 19.12.18.
//

#include "Receiver.h"
#include "OperationCode.h"
#include "Tasks/SenderTasks/SendFilesList.h"
#include "Tasks/SenderTasks/SendNodesList.h"
#include "Tasks/SenderTasks/SendFile.h"
#include <unistd.h>
#include <algorithm>
#include "RemoteNode.h"
#include "NetworkManager.h"
#include "Serializers/Deserializers/Deserializer.h"
#include "Communication/Pullers/SocketPuller.h"

using namespace std;


Receiver::Receiver(RemoteNode* remoteNode): remoteNode(remoteNode) {};


void Receiver::createResponse(int operationCode, int taskId){
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
            SocketPuller puller(remoteNode->getSockfd());
            Deserializer deserializer(&puller);
            auto offsetHash = deserializer.getOffsetAndHash();
            int offset=get<0>(offsetHash);
            int hash=get<1>(offsetHash);
            senderTask = new SendFile(taskId,hash,offset);
            break;
    }
    remoteNode->getSenderTasks()->emplace_back(senderTask);
}

void Receiver::processRequest(int taskId){
    cout<<"Przetwarzam request" << endl;
    auto receiverTasks = remoteNode->getReceiverTasks();
    auto it = find_if(receiverTasks->begin(), receiverTasks->end(), [&taskId](const ReceiverTask* obj) {return obj->getId() == taskId;});
    if (it != receiverTasks->end())
        (*it)->handle(remoteNode->getSockfd());
    else
        cout << "Jest bardzo zle !!! Odebralismy nieznany task nalezy wyrejestrowac noda" << endl;

}

void Receiver::run()
{
    SocketPuller puller(remoteNode->getSockfd());
    Deserializer deserializer(&puller);
    while (!stopRequested())
    {
        if (deserializer.canRead()) {
            try{
                auto data = deserializer.getOperationCodeAndTaskId();
                int operationCode = get<0>(data);
                int taskId = get<1>(data);
                cout<<"Odebralem request: " << operationCode << " " << taskId << endl;
                if (OperationCode::isRequest(operationCode))
                    createResponse(operationCode, taskId);
                else
                    processRequest(taskId);
            }catch (BrokenConnectionException& e){
                cout<<"Node zerwal polaczenie, wyrejectrowuje noda." << endl;
                remoteNode->getNetworkManager()->unregisterRemoteNode(remoteNode);
            }
        }
    }
}
