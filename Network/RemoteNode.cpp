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
#include "../Tasks/ReceiverTasks/ReceiveFile.h"
#include "../Tasks/SenderTasks/FileRequest.h"


RemoteNode::RemoteNode(NodeAddr nodeAddr, NetworkManager* networkManager)
: nodeAddr(nodeAddr), networkManager(networkManager){}


RemoteNode::~RemoteNode(){
//    receiver.stop();
//    sender.stop();
//    close(sockfd);
};


void RemoteNode::addReceiverTask(ReceiverTask* task){
    receiverTasks.emplace_back(task);
}

void RemoteNode::addSenderTask(SenderTask* task){
    senderTasks.emplace_back(task);
}

//
//bool RemoteNode::operator==(const RemoteNode &other){
//    return this->getNodeAddr() == other.getNodeAddr();
//}

vector<ReceiverTask*>* RemoteNode::getReceiverTasks(){
    return &receiverTasks;
}

vector<SenderTask*>* RemoteNode::getSenderTasks(){
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


void RemoteNode::getFileFragment(promise<FileFragment>* filePromise,File file, int offset) {
    int taskId=getId();
    auto senderTask = new FileRequest(taskId,file.hash,offset);
    addSenderTask(senderTask);
    auto receiveTask=new ReceiveFile(taskId,file,offset,filePromise);
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
