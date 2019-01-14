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
#include "../Tasks/SenderTasks/SenderTask.h"
#include "../Tasks/ReceiverTasks/ReceiverTask.h"
#include "../OperationCode.h"
#include <thread>
#include <future>
#include <unistd.h>
#include <mutex>

using  namespace std;

class NetworkManager;

class RemoteNode {
private:
    NodeAddr nodeAddr;
    NetworkManager* networkManager;
    Receiver* receiver;
    Sender* sender;
    vector<ReceiverTask*> receiverTasks;
    vector<SenderTask*> senderTasks;
    mutex mutexSender;
    mutex mutexReceiver;

public:
    RemoteNode(NodeAddr nodeAddr, NetworkManager* networkManager);
    ~RemoteNode();
    vector<ReceiverTask*>* getReceiverTasks();
    vector<SenderTask*>* getSenderTasks();
    NetworkManager *getNetworkManager() const;
    const NodeAddr &getNodeAddr() const;
    void setSenderAndReceiver(Receiver*, Sender*);
public:
    void addReceiverTask(ReceiverTask*);
    void addSenderTask(SenderTask*);
    ReceiverTask* popReceiverTask(int taskId);
    SenderTask* popSenderTask();
    void getFilesList(promise<vector<File>>*);
    vector<NodeAddr> getNodeAddress();
    void getFileFragment(promise<FileFragment>* fragmentPromises, File file,int offset);
};


#endif //P2P_REMOTENODE_H
