//
// Created by michal on 21.12.18.
//

#include "SendFilesListRequest.h"
#include "../../Communication/Pushers/SocketPusher.h"
#include "../../Serializers/Serializers/Serializer.h"


SendFilesListRequest::SendFilesListRequest(int taskId) : SenderTask(taskId) {}


void SendFilesListRequest::send(Output* output) {
    output->requestForFileList(taskId);
}