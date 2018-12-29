//
// Created by michal on 22.12.18.
//

#include <zconf.h>
#include "Client.h"
#include <iostream>


Client::Client(int socketDescriptor): socketDescriptor(socketDescriptor) {}

using namespace std;

void Client::sendInteger(int operationCode){
//    std::cout<<operationCode<<std::endl;
    ssize_t ile_bitow = write(socketDescriptor, &operationCode, sizeof(int));
//    cout<< "Ile bitow zapisano" <<  ile_bitow << endl;
}

void Client::sendFilesNames(vector<File> files){
//    std::cout<<operationCode<<std::endl;
    for(int i=0;i<files.size();i++){
        ssize_t ile_bitow = write(socketDescriptor, &files[i], sizeof(File));
    }
    cout<< "Wyslano liste plikow !!!" << endl;
}

void Client::sendNodeAddr(vector<NodeAddr> nodeAddr) {
    for(int i=0;i<nodeAddr.size();i++){
        ssize_t ile_bitow=write(socketDescriptor,&nodeAddr[i], sizeof(NodeAddr));
    }
    cout<<"Wyslano liste node'ów!"<<endl;
}

int Client::connectWithHost(NodeAddr addr) {
    struct sockaddr_in host_addr;
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = addr.port;
    host_addr.sin_addr = addr.addr;
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;
    if (connect(sock, (struct sockaddr *) &host_addr, sizeof(host_addr)) < 0)
        return -1;
    return sock;
}


void Client::sendFileFragment(FileFragment* fileFragment,int offset) {

    int bity=1048576;
    int fragmentSize=offset+bity;
    if(fragmentSize>fileFragment->file.size)
        fragmentSize=fileFragment->file.size;
    for(int i=offset;i<fragmentSize;i++){
        ssize_t ile_bitow=write(socketDescriptor,&fileFragment->data[i],(size_t)fileFragment->file.size);
    }
    cout<<"Wyslanow fragment pliku"<<endl;
}