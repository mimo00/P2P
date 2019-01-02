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



bool SendFile::isFile(int hash) {
    vector <File> files=FileManager::getFilesNames();
    bool isFile=false;
    for(int i=0; i<files.size();i++)
        if(files.at(i).hash==hash)
            isFile=true;
    return isFile;
}


int SendFile::readyToSend() {
    vector<File> files = FileManager::getFilesNames();
    int portion=OperationCode::PORTION;
    FILE *file;
    for (int i = 0; i < files.size(); i++) {
        if (files.at(i).hash == hash)
            file = fopen(files.at(i).name, "rb");
        if(files.at(i).size <portion)
            portion=files.at(i).size;
        if (file == NULL)
            cout << "File openerror"<<endl;
    }
    //unsigned char buffer[1024]={0};

    //unsigned char buffer[OperationCode::PORTION]={0};


    size_t nread=fread(buffer,1,OperationCode::PORTION,file);
    if(nread>0)
        cout<<"Wyslano fragment pliku"<<endl;
    return nread;
}

void SendFile::send(int socket) {
    if(isFile(hash)&&readyToSend()>0) {
        FileSerializer fileSerializer(socket, OperationCode::FILE_FRAGMENT,id,buffer,readyToSend());
        fileSerializer.send();

    }else {
        CommuniqueSerializer communiqueSerializer(socket, OperationCode::DONT_HAVE_FILE, id);
        communiqueSerializer.send();
    }
}