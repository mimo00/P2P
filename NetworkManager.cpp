//
// Created by michal on 18.12.18.
//
#include "NetworkManager.h"
#include "RemoteNode.h"
#include "Communication/Client.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>

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

    int part=0;
    while(part<filee.size) {
        FileFragment fragment = remoteNodes[0]->getFileFragment(filee, part);
        //cout<<"nastepna runda"<<endl<<endl;
        part += 10;//bajtów offsetu

        //TODO:to co ponizej przeniesc do RemoteNode
        // -> wtedy kazdy watek remoteNode'a bedzie zapisywal do pliku
        // -> dodac zabezpieczenie sprawdzajace czy plik nie otwarty przez inny node
        // -> lub lepiej dzialac na mutexach
        FILE *fp;
        string dir = "./Files/dwnld";
        string file__ = dir + "/" + fragment.file.name;
        fp = fopen(file__.c_str(), "ab");
        if (fp == nullptr)
            cout << "Error while opening file" << endl;
        else {
            fwrite(fragment.data, sizeof(char), fragment.size, fp);
        }
        fclose(fp);
    }
}

NetworkManager::~NetworkManager() {
    for(int i=0;i<remoteNodes.size();i++)
        delete remoteNodes[i];
}
