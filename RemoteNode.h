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


class RemoteNode {
private:
    int sockfd;
    Receiver receiver;
    Sender sender;
    vector<ReceiverTask*> receiverTasks;
    vector<SenderTask*> senderTasks;
    NetworkData* networkData;
public:
    void start();
    RemoteNode(int sockfd, NetworkData* networkData);
    RemoteNode& operator=(RemoteNode && obj);
    RemoteNode(RemoteNode && obj);
    ~RemoteNode();
    bool operator==(const RemoteNode &other);
    vector<ReceiverTask*>* getReceiverTasks();
    vector<SenderTask*>* getSenderTasks();
    void addReceiverTask(ReceiverTask*);
    void addSenderTask(SenderTask*);
    int getSockfd()const{ return this->sockfd; }
    void getFilesList(promise<vector<File>>*);
    vector<NodeAddr> getNodeAddress();
    FileFragment getFileFragment(File file,int offset);
    NetworkData *getNetworkData() const;
};


#endif //P2P_REMOTENODE_H
