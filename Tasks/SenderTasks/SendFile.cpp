//
// Created by pczyz on 28.12.18.
//

#include "SendFile.h"
#include "../../Serializers/CommuniqueSerializer.h"
#include "../../Serializers/FileSerializer.h"
#include "../../FileManager.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <sys/types.h>


FILE* SendFile::getFile(int hash){
    vector <File> files=FileManager::getFilesNames();
    for(int i=0; i<files.size();i++) {
        //cout<<"Sprawdzanie hash'a " << hash << endl;
        if (files.at(i).hash == hash) {
            //cout<<"TAKI SAM !!! " << hash << endl;
            FILE *file;
            file = fopen(FileManager::getFilePath(files.at(i)).c_str(), "rb+");
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
        FileSerializer fileSerializer(socket, OperationCode::FILE_FRAGMENT, id, file);
        fileSerializer.send();
        //fclose(file);
    }else {
        CommuniqueSerializer communiqueSerializer(socket, OperationCode::DONT_HAVE_FILE, id);
        communiqueSerializer.send();
    }
}