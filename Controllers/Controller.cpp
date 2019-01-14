//
// Created by michal on 28.12.18.
//

#include "Controller.h"
#include "../Tasks/ReceiverTasks/ReceiveNodesList.h"
#include "../Factories/NetworkManagerFactory.h"

Controller::Controller(NodeAddr me, string path): me(me), path(path) {
    NetworkManagerFactory socketNetworkManagerFactory;
    networkManager = socketNetworkManagerFactory.createRemoteNode(me, path);
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
    //resumer();    do poprawy
}

vector<NodeAddr> Controller::getNodesAddresses() {
    return networkManager->getNodeAddress();
}

vector<File> Controller::getFiles() {
    return networkManager->getFiles();
}

void Controller::downloadFile(File file){
    networkManager->downloadFile(file);
}

vector<File> Controller::myFiles(){
    FileManager fileManager(path);
    return fileManager.getFilesNames();
}

Controller::~Controller() {
    delete listener;
    delete networkManager;
}

