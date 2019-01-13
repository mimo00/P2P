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
        int operationCode = ntohs(*reinterpret_cast<u_int16_t*>(puller->pullBytes(sizeof(u_int16_t))));
        int taskId = ntohs(*reinterpret_cast<u_int16_t*>(puller->pullBytes(sizeof(u_int16_t))));
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
    int numberOfFiles = ntohs(*reinterpret_cast<u_int16_t*>(puller->pullBytes(sizeof(u_int16_t))));
    for(int i=0;i<numberOfFiles;i++){
        File fileName = *reinterpret_cast<File*>(puller->pullBytes(sizeof(File)));;
        filesNames.push_back(fileName);
    }
    return filesNames;
}

vector<NodeAddr> Deserializer::receiveNodeList() {
    vector<NodeAddr> nodes;
    int numberOfNodes = ntohs(*reinterpret_cast<u_int16_t*>(puller->pullBytes(sizeof(u_int16_t))));
    for(int i=0;i<numberOfNodes;i++){
        NodeAddr nodeAddr = *reinterpret_cast<NodeAddr*>(puller->pullBytes(sizeof(NodeAddr)));;
        nodeAddr.addr.s_addr=ntohl(nodeAddr.addr.s_addr);
        nodeAddr.port=ntohs(nodeAddr.port);
        nodes.push_back(nodeAddr);
    }
    return nodes;
}


tuple<int, int> Deserializer::getOffsetAndHash() {
    try{
        int offset = ntohs(*reinterpret_cast<u_int16_t*>(puller->pullBytes(sizeof(u_int16_t))));
        int hash = ntohs(*reinterpret_cast<u_int16_t*>(puller->pullBytes(sizeof(u_int16_t))));
        return make_tuple(offset, hash);
    } catch (EndOfBytesException& e) {
        throw EndOfDataException();
    }
}

FileFragment Deserializer::receiveFileFragment() {
    FileFragment fileFragment;
    int fileFragmentSize = ntohl(*reinterpret_cast<u_int32_t*>(puller->pullBytes(sizeof(u_int32_t))));
    memcpy(&fileFragment, reinterpret_cast<unsigned char*>(puller->pullBytes(fileFragmentSize)), fileFragmentSize);
    fileFragment.size = fileFragmentSize;
    return fileFragment;
}

NodeAddr Deserializer::receiveListiningAddress() {
    NodeAddr addr;
    addr = *reinterpret_cast<NodeAddr*>(puller->pullBytes(sizeof(NodeAddr)));;
    addr.addr.s_addr=ntohl(addr.addr.s_addr);
    addr.port=ntohs(addr.port);
    return addr;
}

