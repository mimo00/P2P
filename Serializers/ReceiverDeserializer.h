//
// Created by michal on 22.12.18.
//

#ifndef P2P_RECEIVERDESERIALIZER_H
#define P2P_RECEIVERDESERIALIZER_H


#include "../Packages/Package.h"
#include <exception>

using namespace std;

class BrokenConnectionException : public exception
{};

class ReceiverDeserializer {
public:
    ReceiverDeserializer(int);
    Package readData();

private:
    int socketDescriptor;
};


#endif //P2P_RECEIVERDESERIALIZER_H
