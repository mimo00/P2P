//
// Created by michal on 08.01.19.
//

#include <iostream>
#include <cstring>
#include "Deserializer.h"
#include "../../Communication/Pullers/SocketPuller.h"

Deserializer::Deserializer(Puller* puller): Input(puller) {

}

tuple<int, int> Deserializer::getOperationCodeAndTaskId() {
    try{
        int operationCode = *reinterpret_cast<int*>(puller->pullBytes(sizeof(int)));
        int taskId = *reinterpret_cast<int*>(puller->pullBytes(sizeof(int)));
        return make_tuple(operationCode, taskId);
    } catch (EndOfBytesException& e) {
        throw EndOfDataException();
    }
}

bool Deserializer::canRead() {
    return puller->canRead();
}

vector<File> Deserializer::receiveFileList() {
    vector<File> filesNames;
    int numberOfFiles = *reinterpret_cast<int*>(puller->pullBytes(sizeof(int)));
    for(int i=0;i<numberOfFiles;i++){
        File fileName = *reinterpret_cast<File*>(puller->pullBytes(sizeof(File)));;
        filesNames.push_back(fileName);
    }
    return filesNames;
}

vector<NodeAddr> Deserializer::receiveNodeList() {
    vector<NodeAddr> nodes;
    int numberOfNodes = *reinterpret_cast<int*>(puller->pullBytes(sizeof(int)));
    for(int i=0;i<numberOfNodes;i++){
        NodeAddr nodeAddr = *reinterpret_cast<NodeAddr*>(puller->pullBytes(sizeof(NodeAddr)));;
        nodes.push_back(nodeAddr);
    }
    return nodes;
}


tuple<int, int> Deserializer::getOffsetAndHash() {
    try{
        int operationCode = *reinterpret_cast<int*>(puller->pullBytes(sizeof(int)));
        int taskId = *reinterpret_cast<int*>(puller->pullBytes(sizeof(int)));
        return make_tuple(operationCode, taskId);
    } catch (EndOfBytesException& e) {
        throw EndOfDataException();
    }
}

FileFragment Deserializer::receiveFileFragment() {
    FileFragment fileFragment;
    int fileFragmentSize = *reinterpret_cast<int*>(puller->pullBytes(sizeof(int)));
    memcpy(&fileFragment, reinterpret_cast<unsigned char*>(puller->pullBytes(fileFragmentSize)), fileFragmentSize);
    return fileFragment;
}

NodeAddr Deserializer::receiveListiningAddress() {
    NodeAddr addr;
    addr = *reinterpret_cast<NodeAddr*>(puller->pullBytes(sizeof(NodeAddr)));;
    return addr;
}

