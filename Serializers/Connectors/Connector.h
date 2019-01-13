//
// Created by michal on 10.01.19.
//

#ifndef P2P_CONNECTOR_H
#define P2P_CONNECTOR_H


#include "../../OperationCode.h"

class Connector {
protected:
    NodeAddr me;
    int lisiningDescriptor;
public:
    Connector(NodeAddr me);
    const NodeAddr &getMe() const;
    virtual int startListining()=0;
    virtual int initConnectionWithNode(NodeAddr addr)=0;
    virtual tuple<NodeAddr, int> acceptNode()=0;
};


#endif //P2P_CONNECTOR_H
