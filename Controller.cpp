//
// Created by michal on 28.12.18.
//

#include "Controller.h"
#include "Communication/Client.h"
#include "Tasks/ReceiverTasks/ReceiveNodesList.h"

Controller::Controller() {
    networkManager = new NetworkManager();
}

void Controller::startListener(NodeAddr me) {
    listener = new Listener(me.port, networkManager);
    thread listenerThread([&](){listener->run();});
    listenerThread.detach();
}

void Controller::startNewNetwork(NodeAddr me) {
    startListener(me);
}

int Controller::connectToNetwork(NodeAddr me, NodeAddr addr) {
    int result = networkManager->connectToNetwork(addr);
    if (result>0) {
        cout << "Nie udalo sie poloczyc do sieci !" << endl;
        return 1;
    } else{
        startListener(me);
        return 0;
    }

}

vector<NodeAddr> Controller::getNodesAddresses() {
    return networkManager->getNetworkData().getNodeAddress();
}

vector<File> Controller::getFiles() {
    return networkManager->getFiles();
}

vector<File> Controller::searchFile(string name) {
    return networkManager->findFile(name);
}

void Controller::downloadFile(File file){
    networkManager->fileDownloadManage(file);
}




