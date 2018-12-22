//
// Created by michal on 22.12.18.
//

#include <zconf.h>
#include <iostream>
#include "ReceiverDeserializer.h"

using namespace std;

ReceiverDeserializer::ReceiverDeserializer(int socketDescriptor): socketDescriptor(socketDescriptor) {}

Package* ReceiverDeserializer::readData(){
    int operationCode;
    ssize_t ilosc_bitow = read(socketDescriptor, &operationCode, sizeof(int));
    cout << "Wartosc" << operationCode << endl;
    int taskId;
    ssize_t ilosc_bitow2 = read(socketDescriptor, &taskId, sizeof(int));
    cout << "Task Id" << taskId << endl;
}