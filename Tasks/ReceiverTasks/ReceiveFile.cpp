//
// Created by pczyz on 29.12.18.
//

#include "ReceiveFile.h"
#include "../../Serializers/FileDeserializer.h"
#include "../../OperationCode.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>


void ReceiveFile::handle(int socket) {
    FileDeserializer fileDeserializer(socket);
    auto data= fileDeserializer.receive();
    FileFragment fFragment_;
    fFragment_.file=file;
    unsigned char * fragment=get<0>(data);
    int nread=get<1>(data);
    char buffer[nread];
    memset(buffer,'0', sizeof(buffer));
    for(int i=0; i<nread;i++)
        buffer[i]=*(fragment+1);
    FILE *fp;
    fp=fopen(file.name,"ab");
    if(fp==NULL)
        cout<<"Error while opening file"<<endl;
    else {
        fwrite(buffer, 1, nread, fp);
        memcpy(fFragment_.data, buffer, nread);
    }
   fileFragment->set_value(fFragment_);
}
