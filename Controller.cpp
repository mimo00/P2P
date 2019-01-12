//
// Created by michal on 28.12.18.
//

#include "Controller.h"
#include "Communication/Client.h"
#include "Tasks/ReceiverTasks/ReceiveNodesList.h"
#include "Factories/NetworkManagerFactory.h"

Controller::Controller(NodeAddr me): me(me) {
    NetworkManagerFactory socketNetworkManagerFactory;
    networkManager = socketNetworkManagerFactory.createRemoteNode(me);
}

void Controller::startListener() {
    try {
        listener = new Listener(networkManager);
        thread listenerThread([&](){listener->run();});
        listenerThread.detach();
    } catch (ListenerException& e){
        throw ControllerException(e.what());
    }
}

void Controller::startNewNetwork() {
    startListener();
}

void Controller::connectToNetwork(NodeAddr addr) {
    networkManager->connectToNetwork(addr);
    startListener();
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

Controller::~Controller() {
    delete listener;
    delete networkManager;
}


