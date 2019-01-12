//
// Created by michal on 08.01.19.
//

#include "SocketPuller.h"
#include <unistd.h>
#include <cstdio>
#include <sys/select.h>
#include <iostream>


SocketPuller::SocketPuller(int socketDescriptor): socketDescriptor(socketDescriptor) {}


bool SocketPuller::canRead(){
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(socketDescriptor, &rfds);
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    int retval = select(socketDescriptor+1, &rfds, NULL, NULL, &tv);
    if (retval == -1)
        perror("select()");
    return retval != 0;
}


void *SocketPuller::pullBytes(size_t length) {
    void* buffer = new char[length];
    ssize_t readBytes = read(socketDescriptor, buffer, length);
    if (readBytes == 0)
        throw BrokenConnectionException2();
    else
        return buffer;

}


