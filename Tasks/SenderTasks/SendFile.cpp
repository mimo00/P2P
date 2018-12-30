//
// Created by pczyz on 28.12.18.
//

#include "SendFile.h"
#include "../../Serializers/CommuniqueSerializer.h"
#include "../../Serializers/FileSerializer.h"
#include <iostream>
#include <string.h>

void SendFile::send(int socket) {
    FileSerializer fileSerializer(socket,operationCode,id,hash,offset);
    fileSerializer.send();
}
