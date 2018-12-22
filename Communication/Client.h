//
// Created by michal on 22.12.18.
//

#ifndef P2P_CLIENT_H
#define P2P_CLIENT_H


class Client {
public:
    Client(int);
    void sendOperationCode(int operationCode);

private:
    int socketDescriptor;
};


#endif //P2P_CLIENT_H
