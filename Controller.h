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
    Controller(NodeAddr me);
    void startNewNetwork();
    int connectToNetwork(NodeAddr addr);
    vector<NodeAddr> getNodesAddresses();
    vector<File> getFiles();
    void downloadFile(File file);
private:
    NodeAddr me;
    NetworkManager* networkManager;
    Listener* listener;
    void startListener();
};


#endif //P2P_CONTROLLER_H
