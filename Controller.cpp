//
// Created by michal on 28.12.18.
//

#include "Controller.h"
#include "Communication/Client.h"
#include "Tasks/ReceiverTasks/ReceiveNodesList.h"

Controller::Controller(NodeAddr me): me(me) {
    networkManager = new NetworkManager(me);
}

void Controller::startListener() {
    listener = new Listener(me.port, networkManager);
    thread listenerThread([&](){listener->run();});
    listenerThread.detach();
}

void Controller::startNewNetwork() {
    startListener();
}

int Controller::connectToNetwork(NodeAddr addr) {
    int result = networkManager->connectToNetwork(addr, me);
    if (result>0) {
        cout << "Nie udalo sie poloczyc do sieci !" << endl;
        return 1;
    } else{
        startListener();
        return 0;
    }

}

vector<NodeAddr> Controller::getNodesAddresses() {
    return networkManager->getNodeAddress();
}

vector<File> Controller::getFiles() {
    return networkManager->getFiles();
}

void Controller::downloadFile(File file){
    networkManager->fileDownloadManage(file);
}


