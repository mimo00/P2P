//
// Created by michal on 28.12.18.
//

#ifndef P2P_LISTENER_H
#define P2P_LISTENER_H


#include "Stoppable.h"
#include "NetworkManager.h"

class ListenerException : public exception {
private:
    std::string message;
public:
    explicit ListenerException(const std::string& message): message(message){};
    virtual const char* what() const throw() {
        return message.c_str();
    }
};

class Listener: public Stoppable {
public:
    Listener(in_port_t port, NetworkManager* networkManager);
    ~Listener();
    void run();
private:
    int socketDescriptor;
    NetworkManager* networkManager;
};


#endif //P2P_LISTENER_H
