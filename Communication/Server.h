//
// Created by michal on 26.12.18.
//

#ifndef P2P_SERVER_H
#define P2P_SERVER_H

#include <exception>

using  namespace std;

class BrokenConnectionException : public exception
{};

class Server {
public:
    Server(int socketDescriptor);
    int readInteger();
private:
    int socketDescriptor;
};


#endif //P2P_SERVER_H
