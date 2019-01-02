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
    vector<ReceiverTask*> receiverTasks;
    vector<SenderTask*> senderTasks;
    Receiver* receiver;
    Sender* sender;
    void start();
public:
    RemoteNode(int sockfd);
    RemoteNode& operator=(RemoteNode && obj);
    RemoteNode(RemoteNode && obj);
    ~RemoteNode();
    bool operator==(const RemoteNode &other);
    const vector<ReceiverTask*> &getReceiverTasks() const;
    const vector<SenderTask*> &getSenderTasks() const;
    void addReceiverTask(ReceiverTask*);
    void addSenderTask(SenderTask*);
    Receiver *getReceiver() const;
    Sender *getSender() const;
    int getSockfd()const{ return this->sockfd; }
    vector<File> getFilesList(promise<vector<File>>*);
    vector<NodeAddr> getNodeAddress();
    FileFragment getFileFragment(File file,int offset);
    void getSearchedFile(promise<vector<File>>*,string name);
};


#endif //P2P_REMOTENODE_H
