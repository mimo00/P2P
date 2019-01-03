//
// Created by pczyz on 28.12.18.
//

#include "FileSerializer.h"
#include "../Communication/Client.h"

FileSerializer::FileSerializer(int socketDescriptor, int operationCode, int taskId, FILE* file):
socketDescriptor(socketDescriptor),operationCode(operationCode),taskId(taskId), file(file){};

void FileSerializer::send() {
    Client client(socketDescriptor);
    client.sendInteger(operationCode);
    client.sendInteger(taskId);
    char buffer[OperationCode::PORTION];
    size_t nread = fread(buffer, sizeof(char), 10, file);
    client.sendInteger((int)nread);
    client.sendFileFragment(buffer, nread);
}