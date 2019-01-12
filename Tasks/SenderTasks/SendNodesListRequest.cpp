//
// Created by pczyz on 28.12.18.
//

#include <iostream>
#include "SendNodesListRequest.h"
#include "../../Communication/Pushers/SocketPusher.h"
#include "../../Serializers/Serializers/Serializer.h"


SendNodesListRequest::SendNodesListRequest(int taskId) : SenderTask(taskId) {}


void SendNodesListRequest::send(Output* output) {
    output->requestForNodeList(taskId);
    std::cout<<"Wysłałem Liste nodow !!!" << endl;
}
