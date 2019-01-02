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

int FileDeserializer::receiveFileSize() {
    Server server(socketDescriptor);
    int nread = server.readInteger();
    return nread;
}
