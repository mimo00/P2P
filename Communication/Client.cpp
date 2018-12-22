//
// Created by michal on 22.12.18.
//

#include <zconf.h>
#include "Client.h"
#include <iostream>

Client::Client(int socketDescriptor): socketDescriptor(socketDescriptor) {}

using namespace std;

void Client::sendOperationCode(int operationCode){
//    std::cout<<operationCode<<std::endl;
    ssize_t ile_bitow = write(socketDescriptor, &operationCode, sizeof(int));
//    cout<< "Ile bitow zapisano" <<  ile_bitow << endl;
}