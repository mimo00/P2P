//
// Created by michal on 21.12.18.
//

#include "SendFilesListRequest.h"
#include "../../Serializers/CommuniqueSerializer.h"
#include "../../Communication/Pushers/SocketPusher.h"
#include "../../Serializers/Serializers/Serializer.h"


void SendFilesListRequest::send(int socket) {
    SocketPusher socketPusher(socket);
    Serializer serializer(&socketPusher);
    serializer.requestForFileList(id);
}