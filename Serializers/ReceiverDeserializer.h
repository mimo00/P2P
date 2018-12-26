//
// Created by michal on 22.12.18.
//

#ifndef P2P_RECEIVERDESERIALIZER_H
#define P2P_RECEIVERDESERIALIZER_H


#include <exception>
#include <tuple>

using namespace std;

class BrokenConnectionException : public exception
{};

class ReceiverDeserializer {
public:
    ReceiverDeserializer(int);
    tuple<int, int> readData();

private:
    int socketDescriptor;
};


#endif //P2P_RECEIVERDESERIALIZER_H
