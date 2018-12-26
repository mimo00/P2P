//
// Created by michal on 20.12.18.
//

#include "CommuniqueSerializer.h"
#include <iostream>
#include "../Communication/Client.h"

using namespace std;

CommuniqueSerializer::CommuniqueSerializer(int socketDescriptor, int operationCode, int taskId)
: socketDescriptor(socketDescriptor), operationCode(operationCode), taskId(taskId) {}


void CommuniqueSerializer::send(){
    Client client(socketDescriptor);
    client.sendInteger(operationCode);
    client.sendInteger(taskId);
}