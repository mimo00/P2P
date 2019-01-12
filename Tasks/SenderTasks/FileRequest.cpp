//
// Created by pczyz on 29.12.18.
//

#include "FileRequest.h"
#include "../../Communication/Pushers/SocketPusher.h"
#include "../../Serializers/Serializers/Serializer.h"


FileRequest::FileRequest(int taskId, int hash, int offset)
        : SenderTask(taskId), offset(offset),hash(hash){};


void FileRequest::send(Output* output) {
    output->requestForFileFragment(taskId, offset, hash);
}