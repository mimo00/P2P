//
// Created by michal on 18.12.18.
//

#include "RemoteNode.h"

#include <thread>
#include <future>
#include <unistd.h>
#include "Tasks/Task.h"


RemoteNode::RemoteNode(int sockfd): sockfd(sockfd){
    receiverTasks = new vector<Task>;
    receiver = new Receiver(receiverTasks);
    start_receiver();
}

RemoteNode::RemoteNode(RemoteNode && obj) : receiver(obj.receiver)
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


void RemoteNode::start_receiver(){
    std::thread th([&](){receiver->run();});
    th.detach();
}


void RemoteNode::addReceiverTask(Task& task){
    receiverTasks->emplace_back(task);
}


bool RemoteNode::operator==(const RemoteNode &other){
    return this->getSockfd() == other.getSockfd();
}