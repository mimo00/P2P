//
// Created by michal on 22.12.18.
//

#include <zconf.h>
#include "Client.h"
#include <iostream>

Client::Client(int socketDescriptor): socketDescriptor(socketDescriptor) {}

void Client::sendOperationCode(int operationCode){
    std::cout<<operationCode<<std::endl;
    write(socketDescriptor, &operationCode, sizeof(int));
}