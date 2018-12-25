//
// Created by michal on 25.12.18.
//

#include "FilesListSerializer.h"
#include "../Communication/Client.h"

FilesListSerializer::FilesListSerializer(int socketDescriptor, int operationCode, int taskId, vector<File> files)
: socketDescriptor(socketDescriptor), operationCode(operationCode), taskId(taskId), files(files) {}


void FilesListSerializer::send(){
    Client client(socketDescriptor);
    int numberOfFilest = static_cast<int>(files.size());
    client.sendInteger(operationCode);
    client.sendInteger(taskId);
    client.sendInteger(numberOfFilest);
    client.sendFilesNames(files);
}