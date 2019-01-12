//
// Created by michal on 10.01.19.
//

#include "SocketInitializer.h"
#include <zconf.h>
#include <netinet/in.h>

using namespace std;


int SocketInitializer::startListining(NodeAddr me) {
    int socketDescriptor;
    struct sockaddr_in server_addr;
    int addrlen = sizeof(server_addr);
    if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        throw InitializerException("socket failed");
    if (setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &socketDescriptor, sizeof(int)) < 0)
        throw InitializerException("socket option SO_REUSEADDR failed");
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = me.port;
    if(bind(socketDescriptor, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        throw InitializerException("Error while bind");
    if(listen(socketDescriptor, 10) == -1)
        throw InitializerException("Error while listen");
    return  socketDescriptor;
}


int SocketInitializer::connectWithNode(NodeAddr addr) {
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

int SocketInitializer::acceptNode(int lisiningDescriptor) {
    struct sockaddr_in client_addr;
    int addrlen = sizeof(client_addr);
    int nodeSocket = accept(lisiningDescriptor, (struct sockaddr*)&client_addr, (socklen_t*)&addrlen);
    return nodeSocket;
}