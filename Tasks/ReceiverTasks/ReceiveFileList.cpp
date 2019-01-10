//
// Created by michal on 27.12.18.
//

#include <iostream>
#include "ReceiveFileList.h"
#include "../../Serializers/Deserializers/Deserializer.h"
#include "../../Communication/Pullers/SocketPuller.h"


void ReceiveFileList::handle(int socket) {
    SocketPuller puller(socket);
    Deserializer deserializer(&puller);
    vector<File> fileNames_ = deserializer.receiveFileList();
    fileNames->set_value(fileNames_);
}