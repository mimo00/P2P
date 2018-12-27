//
// Created by michal on 18.12.18.
//

#include "RemoteNode.h"

#include <thread>
#include <future>
#include <unistd.h>
#include "Tasks/SenderTasks/SendFilesListRequest.h"
#include "OperationCode.h"


RemoteNode::RemoteNode(int sockfd): sockfd(sockfd){
    receiver = new Receiver(&receiverTasks, &senderTasks, sockfd);
    sender = new Sender(&senderTasks, sockfd);
    start();
}

RemoteNode::RemoteNode(RemoteNode && obj): receiver(obj.receiver)
{
    std::cout << "Move RemoteNode Constructor is called" << std::endl;
}

RemoteNode& RemoteNode::operator=(RemoteNode && obj)
{
    std::cout << "Move RemoteNode Assignment is called" << std::endl;
    receiver = std::move(obj.receiver);
    return *this;
}

RemoteNode::~RemoteNode(){};


void RemoteNode::start(){
    std::thread receiverThread([&](){receiver->run();});
    receiverThread.detach();
    std::thread senderThread([&](){sender->run();});
    senderThread.detach();
}


void RemoteNode::addReceiverTask(ReceiverTask* task){
    receiverTasks.emplace_back(task);
}

void RemoteNode::addSenderTask(SenderTask* task){
    senderTasks.emplace_back(task);
}


bool RemoteNode::operator==(const RemoteNode &other){
    return this->getSockfd() == other.getSockfd();
}

const vector<ReceiverTask*> &RemoteNode::getReceiverTasks() const {
    return receiverTasks;
}

const vector<SenderTask*> &RemoteNode::getSenderTasks() const {
    return senderTasks;
}

Receiver *RemoteNode::getReceiver() const {
    return receiver;
}

Sender *RemoteNode::getSender() const {
    return sender;
}

void RemoteNode::getFilesList(){
    auto senderTask =  new SendFilesListRequest(20);
    addSenderTask(senderTask);
}