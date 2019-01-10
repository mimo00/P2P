//
// Created by michal on 28.12.18.
//

#include "Listener.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../Communication/Server.h"

using namespace std;


Listener::Listener(in_port_t port, NetworkManager* networkManager): networkManager(networkManager) {
    struct sockaddr_in server_addr;
    int addrlen = sizeof(server_addr);
    if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw ListenerException("socket failed");
    if (setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &socketDescriptor, sizeof(int)) < 0)
        throw ListenerException("socket option SO_REUSEADDR failed");
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = port;
    if(bind(socketDescriptor, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        throw ListenerException("Error while bind");
    if(listen(socketDescriptor, 10) == -1)
        throw ListenerException("Error while listen");
}

Listener::~Listener() {
    close(socketDescriptor);
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
                auto remoteNode = new RemoteNode(clientFd, clientAddr, networkManager);
                remoteNode->start();
                networkManager->registerRemoteNode(remoteNode);
            }
        }
    }
}

