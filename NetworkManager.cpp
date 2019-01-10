//
// Created by michal on 18.12.18.
//
#include "NetworkManager.h"
#include "RemoteNode.h"
#include "Communication/Client.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


NetworkManager::NetworkManager(NodeAddr me) {}

void NetworkManager::registerRemoteNode(RemoteNode* remoteNode){
    remoteNodes.push_back(remoteNode);
}

void NetworkManager::unregisterRemoteNode(RemoteNode* remoteNode){
    auto foundRemoteNode = find(remoteNodes.begin(), remoteNodes.end(), remoteNode);
    if(foundRemoteNode == remoteNodes.end())
        throw invalid_argument("Non existing remote node.");
    removeNodeAddress(remoteNode->getNodeAddr());
    delete remoteNode;
    remoteNodes.erase(foundRemoteNode);
}


int NetworkManager::initConnect(NodeAddr addr, NodeAddr me){
    int sockDescriptor;
    if((sockDescriptor = Client::connectWithHost(addr))>=0){
        Client client(sockDescriptor);
        client.sendInteger(me.port);
        return sockDescriptor;
    }
    return -1;
}

int NetworkManager::connect(NodeAddr addr, NodeAddr me){
    int sockDescriptor;
    if((sockDescriptor = Client::connectWithHost(addr))>=0){
        Client client(sockDescriptor);
        client.sendInteger(me.port);
        return sockDescriptor;
    }
    return -1;
}


void NetworkManager::addNodeAddress(NodeAddr nodeAddr) {
    if (nodeAddr != me)
        nodeAddress.push_back(nodeAddr);
}


void NetworkManager::removeNodeAddress(NodeAddr nodeAddr) {
    nodeAddress.erase(std::remove(nodeAddress.begin(), nodeAddress.end(), nodeAddr), nodeAddress.end());
}


const vector<NodeAddr> &NetworkManager::getNodeAddress() const {
    return nodeAddress;
}


int NetworkManager::connectToNetwork(NodeAddr addr, NodeAddr me) {
    int sockDescriptor;
    sockDescriptor = initConnect(addr, me);
    if(sockDescriptor>=0){
        addNodeAddress(addr);
        auto remoteNode = new RemoteNode(sockDescriptor, addr, this);
        remoteNode->start();
        registerRemoteNode(remoteNode);
        vector<NodeAddr> addresses = remoteNode->getNodeAddress();
        for(int i=0;i<addresses.size();i++){
            sockDescriptor = connect(addresses[i], me);
            if(sockDescriptor>=0){
                auto remoteNode = new RemoteNode(sockDescriptor, addresses[i], this);
                registerRemoteNode(remoteNode);
                remoteNode->start();
                addNodeAddress(addresses[i]);
            }
        }
        //tu sprawdzic config i dla kazdego pliku wznowic pobieranie
        return 0;
    } else {
        cout<<"Nie mozna polaczyc z siecia " << endl;
        return -1;
    }
}


vector<File> NetworkManager::getFiles() {
    vector<promise<vector<File>>*> promises(this->remoteNodes.size());
    int i = 0;
    for(int j=0;j<remoteNodes.size();j++) {
        promises[i] = new promise<vector<File>>;
        remoteNodes[i]->getFilesList(promises[i]);
        i++;
    }
    vector<File> files;
    for (int i=0;i<promises.size(); i++){
        future<vector<File>> fileNamesFuture = promises[i]->get_future();
        vector<File> node_files = fileNamesFuture.get();
        files.insert(files.end(), node_files.begin(), node_files.end());
    }
return files;
}

void NetworkManager::fileDownloadManage(File filee) {
    cout << "Pobieram plik " << filee.name << endl;
    downloadManager = new FileDownloadManager(filee,remoteNodes);
    thread downloadThread([&](){downloadManager->Download();});
    downloadThread.detach();
}

NetworkManager::~NetworkManager() {
    for(int i=0;i<remoteNodes.size();i++)
        delete remoteNodes[i];
}
