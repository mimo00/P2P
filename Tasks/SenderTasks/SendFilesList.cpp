//
// Created by michal on 23.12.18.
//

#include "SendFilesList.h"
#include "../../Resources/FileManager.h"
#include "../../Communication/Pushers/SocketPusher.h"
#include "../../Serializers/Serializers/Serializer.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include <string.h>


SendFilesList::SendFilesList(int taskId, FileManager* fileManager)
: SenderTask(taskId), fileManager(fileManager){}


void SendFilesList::send(Output* output) {
    output->sendFileList(taskId, fileManager->getFilesNames());
}

