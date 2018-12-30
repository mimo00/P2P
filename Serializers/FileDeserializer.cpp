//
// Created by pczyz on 29.12.18.
//

#include "FileDeserializer.h"
#include "../Communication/Server.h"

FileDeserializer::FileDeserializer(int socketDescriptor):socketDescriptor(socketDescriptor) {};

FileFragment FileDeserializer::receive() {
    Server server(socketDescriptor);
    int operationCode=server.readInteger();
    int taskId=server.readInteger();
    FileFragment fileFragment;
    //TODO:dokonczyc
    //fileFragment=server.receiveFileFragment();

    return fileFragment;
}
