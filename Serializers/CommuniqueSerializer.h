//
// Created by michal on 20.12.18.
//

#ifndef P2P_REQUESTSERIALIZER_H
#define P2P_REQUESTSERIALIZER_H


#include "../Packages/Package.h"

class CommuniqueSerializer {
public:
    CommuniqueSerializer(int);
    void send(Package package);

private:
    int socketDescriptor;
};


#endif //P2P_REQUESTSERIALIZER_H
