//
// Created by michal on 22.12.18.
//

#include <zconf.h>
#include <iostream>
#include "ReceiverDeserializer.h"

using namespace std;

ReceiverDeserializer::ReceiverDeserializer(int socketDescriptor): socketDescriptor(socketDescriptor) {}

Package ReceiverDeserializer::readData(){
    ssize_t readSize;
    int operationCode;
    readSize = read(socketDescriptor, &operationCode, sizeof(int));
    if (readSize == 0)
        throw BrokenConnectionException();
    else
        cout << "Wartosc " << operationCode << endl;
    int taskId;
    readSize = read(socketDescriptor, &taskId, sizeof(int));
    if (readSize == 0)
        throw BrokenConnectionException();
    else
        cout << "Task Id " << taskId << endl;
    Package package(taskId, operationCode);
    return package;
}