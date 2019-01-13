//
// Created by michal on 08.01.19.
//

#include <stdio.h>
#include "SocketPusher.h"

SocketPusher::SocketPusher(int socketDescriptor): socketDescriptor(socketDescriptor) {}

void SocketPusher::pushBytes(void *bytes, size_t length) {
    ssize_t written_bytes = write(socketDescriptor, bytes, length);
}

SocketPusher::~SocketPusher() {
    close(socketDescriptor);
}
