//
// Created by pczyz on 28.12.18.
//

#include "FileSerializer.h"
#include "../Communication/Client.h"
#include <iostream>

FileSerializer::FileSerializer(int socketDescriptor, int operationCode, int taskId, FILE* file):
socketDescriptor(socketDescriptor),operationCode(operationCode),taskId(taskId), file(file){};

void FileSerializer::send() {
    Client client(socketDescriptor);
    client.sendInteger(operationCode);
    client.sendInteger(taskId);
    char buff[OperationCode::PORTION];
    //char *buff = new char[];
    ssize_t nread = fread(buff, sizeof(char), OperationCode::PORTION, file);
    client.sendInteger((int)nread);
    std::cout<<">>>>>>>>rozmiar buffora "<< sizeof(buff)<<" rozmiar z pliku "<<nread<<endl;
    client.sendFileFragment(buff, nread);
    //delete[] buff;
    //buff= nullptr;
}