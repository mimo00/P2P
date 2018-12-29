//
// Created by pczyz on 28.12.18.
//

#include "FileSerializer.h"
#include "../Communication/Client.h"

FileSerializer::FileSerializer(int socketDescriptor, int operationCode, int taskId, FileFragment* fileFragment,int fileOffset):
socketDescriptor(socketDescriptor),operationCode(operationCode),taskId(taskId),fileFragment(fileFragment),fileOffset(fileOffset){};

void FileSerializer::send() {
    Client client(socketDescriptor);
    client.sendInteger(operationCode);
    client.sendInteger(taskId);
    client.sendInteger(fileOffset);
    client.sendFileFragment(fileFragment,fileOffset);
}