//
// Created by michal on 18.12.18.
//
#include "NetworkManager.h"
#include "RemoteNode.h"
#include "FileDownloadManager.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


NetworkManager::NetworkManager(Connector* connector, RemoteNodeFactory* remoteNodeFactory, FileManager* fileManager)
: connector(connector), remoteNodeFactory(remoteNodeFactory), fileManager(fileManager) {}

void NetworkManager::registerRemoteNode(RemoteNode* remoteNode){
    lock_guard<mutex> lock(mutexReg);
    remoteNodes.push_back(remoteNode);
}

void NetworkManager::unregisterRemoteNode(RemoteNode* remoteNode){
    lock_guard<mutex> lock(mutexReg);
    auto foundRemoteNode = find(remoteNodes.begin(), remoteNodes.end(), remoteNode);
    if(foundRemoteNode == remoteNodes.end())
        throw invalid_argument("Non existing remote node.");
    delete remoteNode;
    remoteNodes.erase(foundRemoteNode);
}


vector<NodeAddr> NetworkManager::getNodeAddress() {
    lock_guard<mutex> lock(mutexReg);
    vector<NodeAddr> nodeAddress;
    for (int i=0;i<remoteNodes.size();i++){
        nodeAddress.push_back(remoteNodes[i]->getNodeAddr());
    }
    return nodeAddress;
}


void NetworkManager::connectToNetwork(NodeAddr addr) {
    int connectionDescription = connector->initConnectionWithNode(addr);
    auto remoteNode = remoteNodeFactory->createRemoteNode(connectionDescription, addr, this);
    registerRemoteNode(remoteNode);
    vector<NodeAddr> addresses = remoteNode->getNodeAddress();
    for(int i=0;i<addresses.size();i++){
        if (addresses[i] != connector->getMe()){
            connectionDescription = connector->initConnectionWithNode(addresses[i]);
            remoteNode = remoteNodeFactory->createRemoteNode(connectionDescription, addresses[i], this);
            registerRemoteNode(remoteNode);
        }
    }
}


vector<File> NetworkManager::getFiles() {
    lock_guard<mutex> lock(mutexReg);
    vector<promise<vector<File>>*> promises(this->remoteNodes.size());
    int i = 0;
    for(int j=0;j<remoteNodes.size();j++) {
        promises[i] = new promise<vector<File>>;
        remoteNodes[i]->getFilesList(promises[i]);
        i++;
    }
    vector<File> files;
    set<File> filesSet;
    for (int i=0;i<promises.size(); i++){
        future<vector<File>> fileNamesFuture = promises[i]->get_future();
        vector<File> node_files = fileNamesFuture.get();
        for(int j=0; j<node_files.size();j++){
            filesSet.insert(node_files[j]);
        }
        //files.insert(files.end(), node_files.begin(), node_files.end());
    }
    for(auto a=filesSet.begin();a!=filesSet.end();a++){
        files.emplace_back(*a);
    }

    return files;
}

void NetworkManager::downloadFile(File file) {
    auto downloadManager = new FileDownloadManager(file, this, fileManager);
    thread downloadThread([&](){downloadManager->Download();});
    downloadThread.detach();
}

void NetworkManager::resumeDownload(string path) {
    FileManager fileManager(path + "/status");
    vector<File> files = fileManager.getFilesNames();
    for(int i=0; i<files.size(); i++) {
        File file =files.at(i);
        if(doResume(file))
            downloadFile(file);
    }
}

bool NetworkManager::doResume(File file){
        string confDir = to_string(file.hash) +"("+file.name+")";;
        fstream config;
        config.open(confDir, fstream::in | fstream::out | fstream::app);
        if (!config)
            cout << "Error while opening status file: " << file.name << endl;
        else {
            string line;
            getline(config, line);
            istringstream row(line);
            int g;
            while(row){
                int g;
                row>>g;
                if(g==0){
                    cout<<"Trzeba wznowic pobieranie"<<endl;
                    config.close();
                    return true;
                }
            }
            config.close();
        }
    return false;
}

RemoteNodeFactory *NetworkManager::getRemoteNodeFactory() const {
    return remoteNodeFactory;
}

Connector *NetworkManager::getConnector() const {
    return connector;
}

FileManager *NetworkManager::getFileManager() const {
    return fileManager;
}

NetworkManager::~NetworkManager() {
    delete connector;
    delete remoteNodeFactory;
    delete fileManager;
    for(int i=0;i<remoteNodes.size();i++)
        delete remoteNodes[i];
}

FileFragment NetworkManager::getFileFragmentFromRemoteNode(File file, int offset) {
    lock_guard<mutex> lock(mutexReg);
    for(int i=0;i<remoteNodes.size();i++) {
        auto fileFragmentPromise = new promise<FileFragment>;
        remoteNodes[i]->getFileFragment(fileFragmentPromise, file, offset);
        FileFragment fileFragment = fileFragmentPromise->get_future().get();
        if(fileFragment.size != 0)
            return fileFragment;
    }
    throw FileNotAvailableOnNetwork();
}
