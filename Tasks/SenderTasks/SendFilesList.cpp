//
// Created by michal on 23.12.18.
//

#include "SendFilesList.h"
#include "../../Serializers/CommuniqueSerializer.h"
#include "../../Serializers/FilesListSerializer.h"
#include "../../FileManager.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include <string.h>


void SendFilesList::send(int socket) {
    FilesListSerializer filesListSerializer(socket, operatinoCode, id, FileManager::getFilesNames());
    filesListSerializer.send();
}

