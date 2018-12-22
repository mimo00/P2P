//
// Created by michal on 20.12.18.
//

#ifndef P2P_REQUESTSERIALIZER_H
#define P2P_REQUESTSERIALIZER_H


#include "../Packages/Package.h"

class SenderSerializer {
public:
    SenderSerializer(int);
    void send(Package package);

private:
    int socketDescriptor;
};


#endif //P2P_REQUESTSERIALIZER_H
