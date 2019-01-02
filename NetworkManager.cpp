//
// Created by michal on 18.12.18.
//
#include "NetworkManager.h"
#include "RemoteNode.h"
#include "Communication/Client.h"
#include <algorithm>
#include <stdexcept>

using namespace std;


NetworkManager::NetworkManager(){}

void NetworkManager::registerRemoteNode(RemoteNode* remoteNode){
    remoteNodes.push_back(remoteNode);
}

void NetworkManager::unregisterRemoteNode(RemoteNode* remoteNode){
    auto foundRemoteNode = find(remoteNodes.begin(), remoteNodes.end(), remoteNode);
    if(foundRemoteNode == remoteNodes.end())
        throw invalid_argument("Non existing remote node.");
    (*foundRemoteNode)->getReceiver()->stop();
    remoteNodes.erase(foundRemoteNode);
}

int NetworkManager::connectToNetwork(NodeAddr addr) {
    int sockDescriptor;
    if((sockDescriptor = Client::connectWithHost(addr))>=0){
        networkData.addNodeAddress(addr);
        auto remoteNode = new RemoteNode(sockDescriptor);
        registerRemoteNode(remoteNode);
        networkData.addNodeAddresses(remoteNode->getNodeAddress());
        return 0;
    } else
        return 1;
}

NetworkData &NetworkManager::getNetworkData() {
    return networkData;
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
    cout<<"Hash " << files[0].hash << endl;
    FileFragment a = remoteNodes[0]->getFileFragment(files[0], 0);
    FILE *fp;
    string dir = "/home/michal/Desktop/TIN_TEST/aaaa";
    string file__ =  dir + "/" + a.file.name;


    fp=fopen(file__.c_str(),"ab");
    if(fp == nullptr)
        cout<<"Error while opening file"<<endl;
    else {
        fwrite(a.data, sizeof(char), a.size, fp);
    }
    fclose(fp);
    return files;
}

void NetworkManager::fileDownloadManage(File file){
    cout<<"Pobieram plik "<<file.name<<endl;
    
    //tutaj pobieranie pliku
}