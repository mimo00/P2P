//
// Created by pczyz on 29.12.18.
//

#include "FileDeserializer.h"
#include "../Communication/Server.h"
#include <zconf.h>
#include <iostream>
#include <tuple>

using namespace std;
FileDeserializer::FileDeserializer(int socketDescriptor):socketDescriptor(socketDescriptor) {};

void FileDeserializer::receive(unsigned char* buff, int nread) {
    Server server(socketDescriptor);
    server.receiveFileFragment(buff, nread);
}

size_t FileDeserializer::receiveFileSize() {
    Server server(socketDescriptor);
    auto nread = (size_t)server.readInteger();
    return nread;
}
