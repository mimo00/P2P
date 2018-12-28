//
// Created by michal on 22.12.18.
//

#include <zconf.h>
#include <iostream>
#include "ReceiverDeserializer.h"
#include "../Communication/Server.h"

using namespace std;

ReceiverDeserializer::ReceiverDeserializer(int socketDescriptor): socketDescriptor(socketDescriptor) {}

tuple<int, int> ReceiverDeserializer::readData(){
    Server server(socketDescriptor);
    int operationCode;
    int taskId;
    try{
        operationCode = server.readInteger();
        taskId = server.readInteger();
        return make_tuple(operationCode, taskId);
    }
    catch (BrokenConnectionException& e){
        throw ReceiverDeserializerException();
    }
}