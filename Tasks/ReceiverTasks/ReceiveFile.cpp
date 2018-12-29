//
// Created by pczyz on 29.12.18.
//

#include "ReceiveFile.h"
#include "../../Serializers/FileDeserializer.h"

void ReceiveFile::handle(int socket) {
    FileDeserializer fileDeserializer(socket);
    FileFragment fileFragment_ = fileDeserializer.receive();
    fileFragment->set_value(fileFragment_);
}
