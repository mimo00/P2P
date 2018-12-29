//
// Created by pczyz on 29.12.18.
//

#include "FileRequest.h"
#include "../../Serializers/CommuniqueSerializer.h"

void FileRequest::send(int socket) {
    CommuniqueSerializer communiqueSerializer(socket, operationCode, id, offset, hash);
    communiqueSerializer.sendFileReq();
}