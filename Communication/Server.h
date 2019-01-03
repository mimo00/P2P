//
// Created by michal on 26.12.18.
//

#ifndef P2P_SERVER_H
#define P2P_SERVER_H

#include <exception>
#include <vector>
#include "../OperationCode.h"

using  namespace std;

class BrokenConnectionException : public exception
{};

class Server {
public:
    Server(int socketDescriptor);
    int readInteger();
    vector<File> receiveFilesNames(int numberOfFiles);
    vector<NodeAddr> receiveNodeAddr(int numberOfAddr);
    void receiveFileFragment(unsigned char * buff, int nread);
private:
    int socketDescriptor;
};


#endif //P2P_SERVER_H
