//
// Created by michal on 20.12.18.
//
#include "../Packages/ListOfFilesPackage.h"

#include "CommuniqueSerializer.h"
#include <iostream>
#include "../Communication/Client.h"

using namespace std;

CommuniqueSerializer::CommuniqueSerializer(int socketDescriptor): socketDescriptor(socketDescriptor) {}


void CommuniqueSerializer::send(Package package){
    cout<<"Wysylam pakiet "<< endl;
    Client client(socketDescriptor);
    client.sendInteger(package.getOperationCode());
    client.sendInteger(package.getTaskId());
}