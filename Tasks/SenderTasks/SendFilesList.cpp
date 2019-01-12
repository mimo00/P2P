//
// Created by michal on 23.12.18.
//

#include "SendFilesList.h"
#include "../../FileManager.h"
#include "../../Communication/Pushers/SocketPusher.h"
#include "../../Serializers/Serializers/Serializer.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include <string.h>


SendFilesList::SendFilesList(int taskId, string path) : SenderTask(taskId), path(path){}


void SendFilesList::send(Output* output) {
    output->sendFileList(taskId, FileManager::getFilesNames(path));
}

