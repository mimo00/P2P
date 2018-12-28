//
// Created by michal on 27.12.18.
//

#include "FileListDeserializer.h"
#include "../Communication/Server.h"

FileListDeserializer::FileListDeserializer(int socketDescriptor): socketDescriptor(socketDescriptor) {}

vector<File> FileListDeserializer::receive(){
    Server server(socketDescriptor);
    int numberOfFiles = server.readInteger();
    vector<File> fileNames = server.receiveFilesNames(numberOfFiles);
    return fileNames;
}