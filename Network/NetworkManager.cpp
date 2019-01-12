//
// Created by michal on 18.12.18.
//
#include "NetworkManager.h"
#include "RemoteNode.h"
#include "../Communication/Client.h"
#include "../FileDownloadManager.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


NetworkManager::NetworkManager(Connector* connector, RemoteNodeFactory* remoteNodeFactory,  Controller* controller)
: connector(connector), remoteNodeFactory(remoteNodeFactory), controller(controller) {}

void NetworkManager::registerRemoteNode(RemoteNode* remoteNode){
    cout<<"Rejestruje !!!"<<endl;
    remoteNodes.push_back(remoteNode);
}

void NetworkManager::unregisterRemoteNode(RemoteNode* remoteNode){
    auto foundRemoteNode = find(remoteNodes.begin(), remoteNodes.end(), remoteNode);
    if(foundRemoteNode == remoteNodes.end())
        throw invalid_argument("Non existing remote node.");
    delete remoteNode;
    remoteNodes.erase(foundRemoteNode);
}


vector<NodeAddr> NetworkManager::getNodeAddress() {
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
    FileDownloadManager manager(filee,remoteNodes);
    if(manager.Download())
        cout << "Pobrano plik!" << endl;
    else
        cout<<"Ten plik już został pobrany"<<endl;
    /*
    int portionSize = OperationCode::PORTION;
    int chunks;
    if(filee.size%portionSize==0)
        chunks =filee.size/portionSize;
    else
        chunks =filee.size/portionSize+1;
    int *parts= new int[chunks]();

    string confDir = "./Files/config/config";
    fstream config;
    config.open(confDir,fstream::in | fstream::out| fstream::app);
    int noHash=0;

    if (!config)
        cout << "Error while opening file" << endl;
    else {
        string line;
        while(getline(config, line)) {
            istringstream row(line);
            int isHash;
            row >> isHash;
            if (isHash == filee.hash) {    //jest hash wiec pobieram do tablicy
                for (int i = 0; i < chunks; i++)
                    row >> parts[i];
                noHash=filee.hash;
            }
        }
        config.close();
    }

    int zeros=0;
    int part=0;
    for(int j=0;j<chunks;j++)
        if(parts[j]==0){
            zeros+=1;
        }
    vector<promise<FileFragment>*> promises(zeros);
    vector<FileFragment> fileFrags;
    int i=0;
    while (zeros>0) {
        for (int j = 0; j < remoteNodes.size() && part < filee.size; j++) {
            promises[i] = new promise<FileFragment>;
            for (int d = 0; d < chunks&&zeros>0; d++) {
                if (parts[d] == 0) {
                    part = d * portionSize;
                    parts[d] = 1;

                    break;
                }
            }
            zeros--;
            remoteNodes[j]->getFileFragment(promises[i], filee, part);
            i++;
        }
    }

    for (int j=0;j<promises.size(); j++){
        future<FileFragment> fileFuture = promises[j]->get_future();
        FileFragment tempfrag=fileFuture.get();
        fileFrags.push_back(tempfrag);
        //fileFrags.emplace(fileFrags.begin(),tempfrag);
    }

    config.open(confDir, fstream::out | fstream::app);
    if (!config)
        cout << "Error while opening file" << endl;
    else {
        if (noHash == 0 && zeros > 0) {         //nie znaleziono hasha, uzupelniam plik config
            config << filee.hash;
            for (int j = 0; j < chunks; j++)
                config << " " <<parts[j];
        }
        config.close();
    }


    FILE *fp;
    string dir = "./Files/dwnld";
    string file__ = dir + "/" + filee.name;
    for(int j=0;j<fileFrags.size();j++) {
        FileFragment fragment = fileFrags.back();
        fileFrags.pop_back();
        fp = fopen(file__.c_str(), "ab");
        fseek(fp, fragment.offset, SEEK_SET);
            if (fp == nullptr)
                cout << "Error while opening file" << endl;
            else {
                fwrite(fragment.data, sizeof(char), fragment.size, fp);
            }
            fclose(fp);
    }
     */
    //TODO:to co ponizej przeniesc do RemoteNode
    // -> dodac zabezpieczenie sprawdzajace czy plik nie otwarty przez inny node
    // -> lub lepiej dzialac na mutexach

}

NetworkManager::~NetworkManager() {
    for(int i=0;i<remoteNodes.size();i++)
        delete remoteNodes[i];
}

RemoteNodeFactory *NetworkManager::getRemoteNodeFactory() const {
    return remoteNodeFactory;
}

Connector *NetworkManager::getConnector() const {
    return connector;
}

Controller *NetworkManager::getController() const {
    return controller;
}
