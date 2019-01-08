//
// Created by michal on 23.12.18.
//

#include "SendFilesList.h"
#include "../../Serializers/CommuniqueSerializer.h"
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


void SendFilesList::send(int socket) {
    SocketPusher socketPusher(socket);
    Serializer serializer(&socketPusher);
    serializer.sendFileList(id, FileManager::getFilesNames());
}

