//
// Created by pczyz on 28.12.18.
//

#include "SendNodesListRequest.h"
#include "../../Serializers/CommuniqueSerializer.h"

void SendNodesListRequest::send(int socket) {
    CommuniqueSerializer communiqueSerializer(socket,operationCode,id);
    communiqueSerializer.send();
}