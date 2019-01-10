//
// Created by michal on 08.01.19.
//

#include <cstring>
#include <vector>
#include "Serializer.h"
#include "../../OperationCode.h"

Serializer::Serializer(Pusher *pusher) : Output(pusher) {}

void Serializer::requestForNodeList(int taskId) {
    int operationCode = OperationCode::NODES_LIST_REQUEST;
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
}

void Serializer::requestForFileList(int taskId) {
    int operatinoCode = OperationCode::FILES_LIST_REQUEST;
    pusher->pushBytes(static_cast<void*>(&operatinoCode), sizeof(operatinoCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
}

void Serializer::requestForFileFragment(int taskId, int offset, int hash) {
    int operationCode = OperationCode::FILE_FRAGMENT_REQUEST;
    pusher->pushBytes(static_cast<void*>(&operationCode), sizeof(operationCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
    pusher->pushBytes(static_cast<void*>(&offset), sizeof(offset));
    pusher->pushBytes(static_cast<void*>(&hash), sizeof(hash));
}

void Serializer::sendNodesList(int taskId, vector<NodeAddr> addresses) {
    int operatinoCode = OperationCode::NODES_LIST;
    int numberOfNodes = addresses.size();
    pusher->pushBytes(static_cast<void*>(&operatinoCode), sizeof(operatinoCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
    pusher->pushBytes(static_cast<void*>(&numberOfNodes), sizeof(taskId));
    for(int i=0;i<numberOfNodes;i++)
        pusher->pushBytes(static_cast<void*>(&addresses[i]), sizeof(NodeAddr));
}

void Serializer::sendFileList(int taskId, vector<File> files) {
    int operatinoCode = OperationCode::NODES_LIST;
    int numberOfFiles = files.size();
    pusher->pushBytes(static_cast<void*>(&operatinoCode), sizeof(operatinoCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
    pusher->pushBytes(static_cast<void*>(&numberOfFiles), sizeof(taskId));
    for(int i=0;i<numberOfFiles;i++)
        pusher->pushBytes(static_cast<void*>(&files[i]), sizeof(File));
}

void Serializer::sendDontHaveFile(int taskId) {
    int operatinoCode = OperationCode::DONT_HAVE_FILE;
    pusher->pushBytes(static_cast<void*>(&operatinoCode), sizeof(operatinoCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
}

void Serializer::sendFileFragment(int taskId, FileFragment fileFragment) {
    int operatinoCode = OperationCode::FILE_FRAGMENT;
    pusher->pushBytes(static_cast<void*>(&operatinoCode), sizeof(operatinoCode));
    pusher->pushBytes(static_cast<void*>(&taskId), sizeof(taskId));
    pusher->pushBytes(static_cast<void*>(&fileFragment.size), sizeof(&fileFragment.size));
    pusher->pushBytes(static_cast<void*>(&fileFragment.data), fileFragment.size);
}
