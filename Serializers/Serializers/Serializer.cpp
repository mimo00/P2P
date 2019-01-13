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
    u_int16_t operationCode = htons(OperationCode::NODES_LIST_REQUEST);
    u_int16_t taskID=htons(taskId);
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskID), sizeof(taskID));
}

void Serializer::requestForFileList(int taskId) {
    u_int16_t operationCode = htons(OperationCode::FILES_LIST_REQUEST);
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
}

void Serializer::requestForFileFragment(int taskId, int offset, int hash) {
    u_int16_t operationCode = htons(OperationCode::FILE_FRAGMENT_REQUEST);
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
    pusher->pushBytes(static_cast<void*>(&offset), sizeof(offset));
    pusher->pushBytes(static_cast<void*>(&hash), sizeof(hash));
}

void Serializer::sendNodesList(int taskId, vector<NodeAddr> addresses) {
    u_int16_t operationCode=htons(OperationCode::NODES_LIST);
    u_int16_t taskID=htons(taskId);
    u_int16_t numberOfNodes= htons(addresses.size());
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskID), sizeof(taskID));
    pusher->pushBytes(static_cast<void*>(&numberOfNodes), sizeof(taskID));
    for(int i=0;i<addresses.size();i++) {
        addresses[i].addr.s_addr=htonl(addresses[i].addr.s_addr);
        addresses[i].port=htons(addresses[i].port);
        pusher->pushBytes(static_cast<void *>(&addresses[i]), sizeof(NodeAddr));
    }
}

void Serializer::sendFileList(int taskId, vector<File> files) {
    u_int16_t operationCode=htons(OperationCode::FILES_LIST);
    u_int16_t taskID=htons(taskId);
    u_int16_t numberOfFiles= htons(files.size());
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskID), sizeof(taskID));
    pusher->pushBytes(static_cast<void*>(&numberOfFiles), sizeof(taskID));
    for(int i=0;i<files.size();i++)
        pusher->pushBytes(static_cast<void*>(&files[i]), sizeof(File));
}

void Serializer::sendDontHaveFile(int taskId) {
    u_int16_t operationCode=htons(OperationCode::DONT_HAVE_FILE);
    u_int16_t taskID=htons(taskId);
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskID), sizeof(taskID));
}

void Serializer::sendFileFragment(int taskId, FileFragment fileFragment) {
    u_int16_t operationCode=htons(OperationCode::FILE_FRAGMENT);
    u_int16_t taskID=htons(taskId);
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskID), sizeof(taskID));
    u_int16_t size=htonl(fileFragment.size);
    pusher->pushBytes(static_cast<void*>(&size), sizeof(fileFragment.size));
    pusher->pushBytes(static_cast<void*>(&fileFragment.data), fileFragment.size);
}

void Serializer::sendListiningAddress(NodeAddr myAddr) {
    myAddr.addr.s_addr=htonl(myAddr.addr.s_addr);
    myAddr.port=htons(myAddr.port);
    pusher->pushBytes(static_cast<void*>(&myAddr), sizeof(myAddr));
}
