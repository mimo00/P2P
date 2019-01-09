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


FILE* SendFile::getFile(int hash){
    vector <File> files=FileManager::getFilesNames();
    for(int i=0; i<files.size();i++) {
        cout<<"Sprawdzanie hash'a " << hash << endl;
        if (files.at(i).hash == hash) {
            cout<<"TAKI SAM !!! " << hash << endl;
            FILE *file;
            file = fopen(FileManager::getFilePath(files.at(i)).c_str(), "rb");
            //file->_offset=10;
            //docelowo offset
            fseek(file,offset,SEEK_SET);
            return file;
        }
    }
    return nullptr;
}

void SendFile::send(int socket) {
    cout<<"Probuje wyslac plik " << endl;
    auto file = getFile(hash);
    if(file != nullptr) {
        FileFragment fileFragment; //To jest tymczasowe
        SocketPusher socketPusher(socket);
        Serializer serializer(&socketPusher);
        serializer.sendFileFragment(id, fileFragment);
        fclose(file);
    }else {
        SocketPusher socketPusher(socket);
        Serializer serializer(&socketPusher);
        serializer.sendDontHaveFile(id);
    }
}