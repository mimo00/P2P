//
// Created by michal on 18.12.18.
//

#ifndef P2P_REMOTENODE_H
#define P2P_REMOTENODE_H

#include <vector>
#include <string>
#include <iostream>
#include "Receiver.h"
#include "Sender.h"
#include "Tasks/SenderTasks/SenderTask.h"
#include "Tasks/ReceiverTasks/ReceiverTask.h"
#include "OperationCode.h"
#include <thread>
#include <future>
#include <unistd.h>

using  namespace std;

class NetworkManager;

class RemoteNode {
private:
    int sockfd;
    NodeAddr nodeAddr;
    NetworkManager* networkManager;
    Receiver receiver;
    Sender sender;
    vector<ReceiverTask*> receiverTasks;
    vector<SenderTask*> senderTasks;
public:
    RemoteNode(int sockfd, NodeAddr nodeAddr, NetworkManager* networkManager);
    ~RemoteNode();
    bool operator==(const RemoteNode &other);
    vector<ReceiverTask*>* getReceiverTasks();
    vector<SenderTask*>* getSenderTasks();
    NetworkManager *getNetworkManager() const;
    const NodeAddr &getNodeAddr() const;
    int getSockfd() const;
public:
    void start();
    void addReceiverTask(ReceiverTask*);
    void addSenderTask(SenderTask*);
    void getFilesList(promise<vector<File>>*);
    vector<NodeAddr> getNodeAddress();
    FileFragment getFileFragment(File file,int offset);

};


#endif //P2P_REMOTENODE_H
