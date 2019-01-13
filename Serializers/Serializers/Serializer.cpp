//
// Created by michal on 08.01.19.
//

#include <cstring>
#include <vector>
#include <iostream>
#include "Serializer.h"
#include "../../OperationCode.h"

Serializer::Serializer(Pusher *pusher) : Output(pusher) {}

void Serializer::requestForNodeList(int taskId) {
    int operationCode = htons(OperationCode::NODES_LIST_REQUEST);
    taskId=htonl(taskId);
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
}

void Serializer::requestForFileList(int taskId) {
    int operationCode = htons(OperationCode::FILES_LIST_REQUEST);
    taskId=htonl(taskId);
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
}

void Serializer::requestForFileFragment(int taskId, int offset, int hash) {
    int operationCode = htons(OperationCode::FILE_FRAGMENT_REQUEST);
    taskId=htonl(taskId);
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
    pusher->pushBytes(static_cast<void*>(&offset), sizeof(offset));
    pusher->pushBytes(static_cast<void*>(&hash), sizeof(hash));
}

void Serializer::sendNodesList(int taskId, vector<NodeAddr> addresses) {
    int operationCode=htons(OperationCode::NODES_LIST);
    taskId=htonl(taskId);
    int numberOfNodes= htonl(addresses.size());
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
    pusher->pushBytes(static_cast<void*>(&numberOfNodes), sizeof(taskId));
    for(int i=0;i<addresses.size();i++) {
        addresses[i].addr.s_addr=htonl(addresses[i].addr.s_addr);
        addresses[i].port=htons(addresses[i].port);
        pusher->pushBytes(static_cast<void *>(&addresses[i]), sizeof(NodeAddr));
    }
}

void Serializer::sendFileList(int taskId, vector<File> files) {
    int operationCode=htons(OperationCode::FILES_LIST);
    taskId=htonl(taskId);
    int numberOfFiles= htonl(files.size());
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
    pusher->pushBytes(static_cast<void*>(&numberOfFiles), sizeof(numberOfFiles));
    for(int i=0;i<files.size();i++)
        pusher->pushBytes(static_cast<void*>(&files[i]), sizeof(File));
}

void Serializer::sendDontHaveFile(int taskId) {
    int operationCode=htons(OperationCode::DONT_HAVE_FILE);
    taskId=htonl(taskId);
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
}

void Serializer::sendFileFragment(int taskId, FileFragment fileFragment) {
    int operationCode=htons(OperationCode::FILE_FRAGMENT);
    taskId=htonl(taskId);
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
    int sizeFile=htonl(fileFragment.size);
    pusher->pushBytes(static_cast<void*>(&sizeFile), sizeof(sizeFile));
    pusher->pushBytes(static_cast<void*>(&fileFragment.data), size_t(fileFragment.size));
}

void Serializer::sendListiningAddress(NodeAddr myAddr) {
    myAddr.addr.s_addr=htonl(myAddr.addr.s_addr);
    myAddr.port=htons(myAddr.port);
    pusher->pushBytes(static_cast<void*>(&myAddr), sizeof(myAddr));
}
