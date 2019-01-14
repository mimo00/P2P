//
// Created by michal on 19.12.18.
//

#include "Receiver.h"
#include "../OperationCode.h"
#include "../Tasks/SenderTasks/SendFilesList.h"
#include "../Tasks/SenderTasks/SendNodesList.h"
#include "../Tasks/SenderTasks/SendFile.h"
#include <unistd.h>
#include <algorithm>
#include "RemoteNode.h"
#include "NetworkManager.h"
#include "../Serializers/Deserializers/Deserializer.h"
#include "../Communication/Pullers/SocketPuller.h"
#include "../Controllers/Controller.h"

using namespace std;


Receiver::Receiver(RemoteNode* remoteNode, Input* input, FileManager* fileManager)
: remoteNode(remoteNode), input(input), fileManager(fileManager) {};


void Receiver::createResponse(int operationCode, int taskId){
    SenderTask* senderTask;
    switch (operationCode) {
        case OperationCode::FILES_LIST_REQUEST:
            senderTask = new SendFilesList(taskId, fileManager);
            break;
        case OperationCode::NODES_LIST_REQUEST:
            senderTask = new SendNodesList(taskId, remoteNode->getNetworkManager()->getNodeAddress());
            break;
        case OperationCode::FILE_FRAGMENT_REQUEST:
            auto offsetHash = input->getOffsetAndHash();
            int offset=get<0>(offsetHash);
            int hash=get<1>(offsetHash);
            senderTask = new SendFile(taskId,hash,offset, fileManager);
            break;
    }
    remoteNode->addSenderTask(senderTask);
}

void Receiver::processRequest(int operationCode, int taskId){
    auto receiverTask = remoteNode->popReceiverTask(taskId);
    if (receiverTask != nullptr)
        receiverTask->handle(operationCode, input);
    else
        cout << "Odebralismy nieznany task" << endl;
}

void Receiver::run()
{
    while (!stopRequested())
    {
        if (input->canRead()) {
            try{
                auto data = input->getOperationCodeAndTaskId();
                int operationCode = get<0>(data);
                int taskId = get<1>(data);
                cout<<"Odebralem request: " << operationCode << " " << taskId << endl;
                if (OperationCode::isRequest(operationCode))
                    createResponse(operationCode, taskId);
                else
                    processRequest(operationCode, taskId);
            }catch (EndOfDataException& e){
                cout<<"Node zerwal polaczenie, wyrejectrowuje noda." << endl;
                remoteNode->closeTasks();
                remoteNode->getNetworkManager()->unregisterRemoteNode(remoteNode);
                return;
            }
        }
    }
}

Receiver::~Receiver() {
    delete input;
}
