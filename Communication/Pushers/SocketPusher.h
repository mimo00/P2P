//
// Created by michal on 08.01.19.
//

#ifndef P2P_SOCKETPUSHER_H
#define P2P_SOCKETPUSHER_H


#include "Pusher.h"
#include <unistd.h>

class SocketPusher: public Pusher {
public:
    SocketPusher(int socketDescriptor);
    ~SocketPusher();
private:
    int socketDescriptor;
    void pushBytes(void* bytes, size_t length);
};


#endif //P2P_SOCKETPUSHER_H
