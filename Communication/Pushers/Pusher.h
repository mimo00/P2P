//
// Created by michal on 08.01.19.
//

#ifndef P2P_PUSHER_H
#define P2P_PUSHER_H

#include <unistd.h>
#include <exception>

using namespace std;

class CantPushBytesException : public exception {};

class Pusher {
public:
    virtual void pushBytes(void* bytes, size_t length)=0;
};


#endif //P2P_PUSHER_H
