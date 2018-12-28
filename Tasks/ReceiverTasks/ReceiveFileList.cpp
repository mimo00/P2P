//
// Created by michal on 27.12.18.
//

#include <iostream>
#include "ReceiveFileList.h"
#include "../../Serializers/FileListDeserializer.h"


void ReceiveFileList::handle(int socket) {
    FileListDeserializer fileListDeserializer(socket);
    vector<File> a = fileListDeserializer.receive();
}