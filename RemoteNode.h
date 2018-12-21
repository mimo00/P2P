//
// Created by michal on 18.12.18.
//

#ifndef P2P_REMOTENODE_H
#define P2P_REMOTENODE_H

#include <vector>
#include <string>
#include <iostream>
#include "Tasks/Task.h"
#include "Receiver.h"
#include "Sender.h"
#include <thread>
#include <future>
#include <unistd.h>

using  namespace std;


class RemoteNode {
private:
    int sockfd;
    vector<Task> receiverTasks;
    vector<Task> senderTasks;
    Receiver* receiver;
    Sender* sender;
    void start();
public:
    RemoteNode(int sockfd);
    RemoteNode& operator=(RemoteNode && obj);
    RemoteNode(RemoteNode && obj);
    ~RemoteNode();
    bool operator==(const RemoteNode &other);
    const vector<Task> &getReceiverTasks() const;
    const vector<Task> &getSenderTasks() const;
    void addReceiverTask(Task&);
    void addSenderTask(Task&);
    Receiver *getReceiver() const;
    Sender *getSender() const;
    int getSockfd()const{ return this->sockfd; }
};


#endif //P2P_REMOTENODE_H
