//
// Created by pczyz on 30.12.18.
//

#include "SendResponse.h"
#include "../../Serializers/CommuniqueSerializer.h"

void SendResponse::send(int socket) {
    CommuniqueSerializer serializer(socket,operationCode,id);
    serializer.send();
}
