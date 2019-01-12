//
// Created by michal on 11.01.19.
//

#include "NetworkManagerFactory.h"
#include "../Serializers/Connectors/HostConnector.h"
#include "SocketRemoteNodeFactory.h"

NetworkManager *NetworkManagerFactory::createRemoteNode(NodeAddr me, string path) {
    auto connector = new HostConnector(me);
    auto remoteNodeFactory = new SocketRemoteNodeFactory();
    auto fileManager = new FileManager(path);
    auto networkManager = new NetworkManager(connector, remoteNodeFactory, fileManager);
    return networkManager;
}
