//
// Created by pczyz on 28.12.18.
//

#include "FileSerializer.h"
#include "../Communication/Client.h"

FileSerializer::FileSerializer(int socketDescriptor, int operationCode, int taskId, unsigned char buffer[OperationCode::PORTION],int nread):
socketDescriptor(socketDescriptor),operationCode(operationCode),taskId(taskId), nread(nread){buff=buffer;};

void FileSerializer::send() {
    Client client(socketDescriptor);
    client.sendInteger(operationCode);
    client.sendInteger(taskId);
    client.sendInteger(nread);
    client.sendFileFragment(buff,nread);
}