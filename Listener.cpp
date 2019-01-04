//
// Created by michal on 28.12.18.
//

#include "Listener.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Communication/Server.h"

using namespace std;


Listener::Listener(in_port_t port, NetworkManager* networkManager): networkManager(networkManager) {
    struct sockaddr_in server_addr;
    int addrlen = sizeof(server_addr);
    if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = port;
    if(bind(socketDescriptor, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Error in bind\n");
        exit(1);
    }
    if(listen(socketDescriptor, 10) == -1) {
        printf("Failed to listen\n");
        exit(1);
    }
}


void Listener::run() {
    while (!stopRequested()) {
        struct sockaddr_in client_addr;
        int addrlen = sizeof(client_addr);
        int clientFd = 1;
        cout<<"Nasluchuje na sockecie " << socketDescriptor << endl;
        while(clientFd > 0) {
            clientFd = accept(socketDescriptor, (struct sockaddr*)&client_addr, (socklen_t*)&addrlen);
            if(clientFd<0) {
                perror("Error in accept\n");
                continue;
            } else{
                cout<<"Rejestruje Noda !!!" << endl;
                Server server(clientFd);
                int port = server.readInteger();
                NodeAddr clientAddr;
                clientAddr.port = port;
                clientAddr.addr = client_addr.sin_addr;
                networkManager->addNodeAddress(clientAddr);
                auto remoteNode = new RemoteNode(clientFd, networkManager);
                remoteNode->start();
                networkManager->registerRemoteNode(remoteNode);
            }
        }
    }
}


