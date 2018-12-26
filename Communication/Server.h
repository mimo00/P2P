//
// Created by michal on 26.12.18.
//

#ifndef P2P_SERVER_H
#define P2P_SERVER_H


class Server {
public:
    Server(int socketDescriptor);
private:
    int socketDescriptor;
    int readInteger();
};


#endif //P2P_SERVER_H
