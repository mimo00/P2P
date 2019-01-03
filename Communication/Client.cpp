//
// Created by michal on 22.12.18.
//

#include <zconf.h>
#include "Client.h"
#include <iostream>
#include "../Tasks/SenderTasks/SendFilesList.h"


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


void Client::sendFileFragment(char* buff,int nread) {
    if(nread>0) {
        ssize_t ile_bitow = write(socketDescriptor, buff, nread);
        cout << "Wyslanow fragment pliku:" << (int) ile_bitow << " bajtow" << endl;
    }
}