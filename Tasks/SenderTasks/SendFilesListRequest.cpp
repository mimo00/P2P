//
// Created by michal on 21.12.18.
//

#include "SendFilesListRequest.h"
#include "../../Serializers/CommuniqueSerializer.h"


void SendFilesListRequest::send(int socket) {
    CommuniqueSerializer communiqueSerializer(socket, operatinoCode, id);
    communiqueSerializer.send();
}