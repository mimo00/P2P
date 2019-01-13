//
// Created by michal on 10.01.19.
//

#ifndef P2P_HOSTCONNECTOR_H
#define P2P_HOSTCONNECTOR_H


#include "../../OperationCode.h"
#include "Connector.h"

class HostConnector: public Connector {
public:
    HostConnector(NodeAddr me);
    ~HostConnector();
    int startListining() override;
    int initConnectionWithNode(NodeAddr addr) override;
    tuple<NodeAddr, int> acceptNode() override;
};


#endif //P2P_HOSTCONNECTOR_H