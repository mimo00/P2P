//
// Created by michal on 28.12.18.
//

#ifndef P2P_CONTROLLER_H
#define P2P_CONTROLLER_H


#include "OperationCode.h"
#include "Listener.h"
#include "NetworkManager.h"
#include "NetworkData.h"

using namespace std;

class Controller {
public:
    Controller();
    void startNewNetwork(NodeAddr me);
    int connectToNetwork(NodeAddr me, NodeAddr addr);
    vector<NodeAddr> getNodesAddresses();
    vector<File> getFiles();
    void downloadFile(File file);
private:
    NetworkManager* networkManager;
    Listener* listener;
    void startListener(NodeAddr me);
};


#endif //P2P_CONTROLLER_H
