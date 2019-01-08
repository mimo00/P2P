//
// Created by pczyz on 28.12.18.
//

#include <iostream>
#include "SendNodesListRequest.h"
#include "../../Serializers/CommuniqueSerializer.h"
#include "../../Communication/Pushers/SocketPusher.h"
#include "../../Serializers/Serializers/Serializer.h"

void SendNodesListRequest::send(int socket) {
    SocketPusher socketPusher(socket);
    Serializer serializer(&socketPusher);
    serializer.requestForNodeList(id);
    std::cout<<"Wysłałem Liste nodow !!!" << endl;
}