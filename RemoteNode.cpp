//
// Created by michal on 18.12.18.
//

#include "RemoteNode.h"

#include <thread>
#include <future>
#include <unistd.h>
#include <cstdlib>
#include "Tasks/SenderTasks/SendFilesListRequest.h"
#include "OperationCode.h"
#include "Tasks/ReceiverTasks/ReceiveFileList.h"
#include "Tasks/SenderTasks/SendNodesListRequest.h"
#include "Tasks/ReceiverTasks/ReceiveNodesList.h"
#include "Tasks/ReceiverTasks/ReceiveFile.h"
#include "Tasks/SenderTasks/FileRequest.h"


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

RemoteNode::~RemoteNode(){
    cout<<"Destruktor" << endl;
    receiver->stop();
    sender->stop();
};


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

int getId(){
    srand(time(NULL));
    return rand();
}

void RemoteNode::getFilesList(promise<vector<File>>* fileNamesPromise){
    cout<<"ODPALAM getFilesList" << endl;
    int taskId = getId();
    auto senderTask =  new SendFilesListRequest(taskId);
    addSenderTask(senderTask);
    auto receiveTask = new ReceiveFileList(taskId, fileNamesPromise);
    addReceiverTask(receiveTask);
}

vector<NodeAddr> RemoteNode::getNodeAddress() {
    int taskId = getId();
    auto senderTask =  new SendNodesListRequest(taskId);
    addSenderTask(senderTask);
    promise<vector<NodeAddr>> nodeAddressPromise;
    future<vector<NodeAddr>> nodeAddressFuture = nodeAddressPromise.get_future();
    auto receiveTask = new ReceiveNodesList(taskId, &nodeAddressPromise);
    addReceiverTask(receiveTask);
    vector<NodeAddr> nodesAddress = nodeAddressFuture.get();
    return nodesAddress;
}


FileFragment RemoteNode::getFileFragment(File file, int offset) {
    int taskId=getId();
    auto senderTask = new FileRequest(taskId,file.hash,offset);
    addSenderTask(senderTask);
    promise<FileFragment> filePromise;
    future<FileFragment> fileFuture=filePromise.get_future();
    auto receiveTask=new ReceiveFile(taskId,file,offset,&filePromise);
    addReceiverTask(receiveTask);
    FileFragment fragment=fileFuture.get();



    return fragment;
}