//
// Created by michal on 08.01.19.
//

#ifndef P2P_SOCKETPULLER_H
#define P2P_SOCKETPULLER_H


#include "Puller.h"
#include <exception>

using namespace std;

class NoDataExceptionInSocket : public exception
{};

class BrokenConnectionException : public exception
{};

class SocketPuller: public Puller {
public:
    SocketPuller(int socketDescriptor);
    void *pullBytes(size_t length) override;
    bool canRead() override;
private:
    int socketDescriptor;
};


#endif //P2P_SOCKETPULLER_H
