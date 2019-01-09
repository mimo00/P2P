//
// Created by pczyz on 29.12.18.
//

#include "FileRequest.h"
#include "../../Communication/Pushers/SocketPusher.h"
#include "../../Serializers/Serializers/Serializer.h"

void FileRequest::send(int socket) {
    SocketPusher socketPusher(socket);
    Serializer serializer(&socketPusher);
    serializer.requestForFileFragment(id, offset, hash);
}