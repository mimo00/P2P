//
// Created by michal on 10.01.19.
//

#ifndef P2P_CONNECTER_H
#define P2P_CONNECTER_H


#include "../../OperationCode.h"
#include <string>

class Initializer {
public:
    virtual int startListining(NodeAddr me)=0;
    virtual int connectWithNode(NodeAddr addr)=0;
    virtual int acceptNode(int lisiningDescriptor)=0;
};


class InitializerException : public exception {
private:
    std::string message;
public:
    explicit InitializerException(const std::string& message): message(message){};
    virtual const char* what() const throw() {
        return message.c_str();
    }
};

#endif //P2P_CONNECTER_H
