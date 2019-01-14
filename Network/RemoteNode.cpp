//
// Created by michal on 18.12.18.
//

#include "RemoteNode.h"

#include <thread>
#include <future>
#include <unistd.h>
#include <cstdlib>
#include "../Tasks/SenderTasks/SendFilesListRequest.h"
#include "../OperationCode.h"
#include "../Tasks/ReceiverTasks/ReceiveFileList.h"
#include "../Tasks/SenderTasks/SendNodesListRequest.h"
#include "../Tasks/ReceiverTasks/ReceiveNodesList.h"
#include "../Tasks/ReceiverTasks/ReceiveFileFragment.h"
#include "../Tasks/SenderTasks/FileRequest.h"


RemoteNode::RemoteNode(NodeAddr nodeAddr, NetworkManager* networkManager)
: nodeAddr(nodeAddr), networkManager(networkManager){}


RemoteNode::~RemoteNode(){
    receiver->stop();
    sender->stop();
    delete receiver;
    delete sender;
};


void RemoteNode::addReceiverTask(ReceiverTask* task){
    lock_guard<mutex> lock(mutexReceiver);
    receiverTasks.emplace_back(task);
}

void RemoteNode::addSenderTask(SenderTask* task){
    lock_guard<mutex> lock(mutexSender);
    senderTasks.emplace_back(task);
}


ReceiverTask* RemoteNode::popReceiverTask(int taskId) {
    lock_guard<mutex> lock(mutexReceiver);
    auto it = find_if(receiverTasks.begin(), receiverTasks.end(), [&taskId](const ReceiverTask* obj) {return obj->getTaskId() == taskId;});
    if (it != receiverTasks.end()){
        receiverTasks.erase(it);
        return *it;
    }
    else
        return nullptr;
}


SenderTask* RemoteNode::popSenderTask() {
    return nullptr;
}


vector<ReceiverTask*>* RemoteNode::getReceiverTasks(){
    lock_guard<mutex> lock(mutexReceiver);
    return &receiverTasks;
}

vector<SenderTask*>* RemoteNode::getSenderTasks(){
    lock_guard<mutex> lock(mutexSender);
    return &senderTasks;
}

int getId(){
    return rand();
}

void RemoteNode::getFilesList(promise<vector<File>>* fileNamesPromise){
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


void RemoteNode::getFileFragment(promise<FileFragment>* filePromise, File file, int offset) {
    int taskId=getId();
    auto senderTask = new FileRequest(taskId,file.hash, offset);
    addSenderTask(senderTask);
    auto receiveTask=new ReceiveFileFragment(taskId, filePromise);
    addReceiverTask(receiveTask);
}

NetworkManager *RemoteNode::getNetworkManager() const {
    return networkManager;
}

const NodeAddr &RemoteNode::getNodeAddr() const {
    return nodeAddr;
}

void RemoteNode::setSenderAndReceiver(Receiver* receiver_, Sender *sender_) {
    receiver=receiver_;
    sender=sender_;
    thread receiverThread([&](){receiver->run();});
    receiverThread.detach();
    std::thread senderThread([&](){sender->run();});
    senderThread.detach();
}
