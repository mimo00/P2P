//
// Created by michal on 26.12.18.
//

#include "Server.h"
#include <zconf.h>
#include <iostream>

Server::Server(int socketDescriptor)
: socketDescriptor(socketDescriptor) {};


int Server::readInteger() {
    int value;
    ssize_t readSize;
    readSize = read(socketDescriptor, &value, sizeof(int));
    if (readSize == 0)
        throw BrokenConnectionException();
    else
        return value;
};

vector<File> Server::receiveFilesNames(int numberOfFiles){
    ssize_t readSize;
    vector<File> filesNames;
    for(int i=0;i<numberOfFiles;i++){
        File fileName;
        readSize = read(socketDescriptor, &fileName, sizeof(File));
        if (readSize == 0)
            throw BrokenConnectionException();
        filesNames.push_back(fileName);
    }
    return filesNames;
}

vector<NodeAddr> Server::receiveNodeAddr(int numberOfFiles){
    ssize_t readSize;
    vector<NodeAddr> nodeAddr;
    for(int i=0;i<numberOfFiles;i++){
        NodeAddr addr;
        readSize = read(socketDescriptor, &addr, sizeof(NodeAddr));
        if (readSize == 0)
            throw BrokenConnectionException();
        nodeAddr.push_back(addr);
    }
    return nodeAddr;
}
