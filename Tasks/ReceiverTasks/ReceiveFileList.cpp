//
// Created by michal on 27.12.18.
//

#include <iostream>
#include "ReceiveFileList.h"
#include "../../Serializers/Deserializers/Deserializer.h"
#include "../../Communication/Pullers/SocketPuller.h"


ReceiveFileList::ReceiveFileList(int id, promise<vector<File>> *fileNames)
        : ReceiverTask(id), fileNames(fileNames){}


void ReceiveFileList::handle(int ,Input* input) {
    vector<File> fileNames_ = input->receiveFileList();
    fileNames->set_value(fileNames_);
}

void ReceiveFileList::close() {
    vector<File> fileNames_ = vector<File>(0);
    fileNames->set_value(fileNames_);
}
