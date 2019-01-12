//
// Created by michal on 10.01.19.
//

#ifndef P2P_SOCKETCONNECTER_H
#define P2P_SOCKETCONNECTER_H


#include "Initializer.h"

class SocketInitializer: public Initializer {
public:
    int startListining(NodeAddr me);
    int connectWithNode(NodeAddr addr) override;
    int acceptNode(int lisiningDescriptor) override;
};




#endif //P2P_SOCKETCONNECTER_H
