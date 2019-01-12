//
// Created by pczyz on 28.12.18.
//

#include "SendFile.h"
#include "../../FileManager.h"
#include "../../Communication/Pushers/SocketPusher.h"
#include "../../Serializers/Serializers/Serializer.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <sys/types.h>


SendFile::SendFile(int taskId, int hash, int offset, string path)
        : SenderTask(taskId),hash(hash),offset(offset), path(path){}


void SendFile::send(Output* output) {
    FileFragment fileFragment = FileManager::getFile(path, hash, offset);
    if(fileFragment.size != -1) {
        output->sendFileFragment(taskId, fileFragment);
    }else {
        output->sendDontHaveFile(taskId);
    }
}