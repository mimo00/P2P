//
// Created by michal on 11.01.19.
//

#include "NetworkManagerFactory.h"
#include "../Serializers/Connectors/HostConnector.h"
#include "SocketRemoteNodeFactory.h"

NetworkManager *NetworkManagerFactory::createRemoteNode(NodeAddr me) {
    auto connector = new HostConnector(me);
    auto remoteNodeFactory = new SocketRemoteNodeFactory();
    auto networkManager = new NetworkManager(connector, remoteNodeFactory);
    return networkManager;
}
