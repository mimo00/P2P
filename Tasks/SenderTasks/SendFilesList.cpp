//
// Created by michal on 23.12.18.
//

#include "SendFilesList.h"
#include "../../Serializers/CommuniqueSerializer.h"
#include "../../Serializers/FilesListSerializer.h"
#include <iostream>


vector<File> SendFilesList::getFilesNames(){
    vector<File> files;
    File f;
    f.size = 10;
    f.hash = 3;
    string s = "Jakis napis";
    s.copy(f.name, 64);
    files.push_back(f);
    return files;
}


void SendFilesList::send(int socket) {
    FilesListSerializer filesListSerializer(socket, operatinoCode, id, getFilesNames());
    filesListSerializer.send();
}