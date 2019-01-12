//
// Created by michal on 08.01.19.
//

#ifndef P2P_PULLER_H
#define P2P_PULLER_H

#include <unistd.h>
#include <exception>

using namespace std;

class EndOfBytesException : public exception {};

class Puller {
public:
    virtual void* pullBytes(size_t length)=0;
    virtual bool canRead()=0;
};


#endif //P2P_PULLER_H
