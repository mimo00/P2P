//
// Created by michal on 11.01.19.
//

#ifndef P2P_SOCKETNETWORKMANAGERFACTORY_H
#define P2P_SOCKETNETWORKMANAGERFACTORY_H


#include "../Network/NetworkManager.h"

class NetworkManagerFactory {
public:
    NetworkManager *createRemoteNode(NodeAddr me);
};


#endif //P2P_SOCKETNETWORKMANAGERFACTORY_H
