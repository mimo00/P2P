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


void Server::receiveFileFragment(unsigned char* buff, int nread) {
    ssize_t readSize;
    unsigned char bufff[OperationCode::PORTION];
    readSize=read(socketDescriptor, buff, nread);
    if (readSize == 0)
        throw BrokenConnectionException();
    cout<<"Przeczytano: " << readSize << " bajtow pliku" << endl;
}
