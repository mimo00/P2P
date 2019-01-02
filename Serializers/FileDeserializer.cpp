//
// Created by pczyz on 29.12.18.
//

#include "FileDeserializer.h"
#include "../Communication/Server.h"
#include <zconf.h>
using namespace std;
FileDeserializer::FileDeserializer(int socketDescriptor):socketDescriptor(socketDescriptor) {};

tuple<unsigned char *,int> FileDeserializer::receive() {
    Server server(socketDescriptor);
    int nread = server.readInteger();
    unsigned char *buffp=server.receiveFileFragment(nread);

    //FileFragment fileFragment;
    //TODO:dokonczyc
    //fileFragment=server.receiveFileFragment();

    return make_tuple(buffp,nread);
}