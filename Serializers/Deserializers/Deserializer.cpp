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
        int operationCode = ntohs(*reinterpret_cast<int*>(puller->pullBytes(sizeof(int))));
        int taskId = ntohl(*reinterpret_cast<int*>(puller->pullBytes(sizeof(int))));
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
    try{
        int numberOfFiles = ntohl(*reinterpret_cast<int*>(puller->pullBytes(sizeof(int))));
        for(int i=0;i<numberOfFiles;i++){
            File fileName = *reinterpret_cast<File*>(puller->pullBytes(sizeof(File)));;
            filesNames.push_back(fileName);
        }
    } catch (EndOfBytesException& e) {
        throw EndOfDataException();
    }
    return filesNames;
}

vector<NodeAddr> Deserializer::receiveNodeList() {
    vector<NodeAddr> nodes;
    try{
        int numberOfNodes = ntohl(*reinterpret_cast<int*>(puller->pullBytes(sizeof(int))));
        for(int i=0;i<numberOfNodes;i++){
            NodeAddr nodeAddr = *reinterpret_cast<NodeAddr*>(puller->pullBytes(sizeof(NodeAddr)));;
            nodeAddr.addr.s_addr=ntohl(nodeAddr.addr.s_addr);
            nodeAddr.port=ntohs(nodeAddr.port);
            nodes.push_back(nodeAddr);
        }
    } catch (EndOfBytesException& e) {
        throw EndOfDataException();
    }
    return nodes;
}

tuple<int, int> Deserializer::getOffsetAndHash() {
    try{
        int offset = ntohl(*reinterpret_cast<int*>(puller->pullBytes(sizeof(int))));
        int hash = ntohl(*reinterpret_cast<int*>(puller->pullBytes(sizeof(int))));
        return make_tuple(offset, hash);
    } catch (EndOfBytesException& e) {
        throw EndOfDataException();
    }
}

FileFragment Deserializer::receiveFileFragment() {
    try{
        FileFragment fileFragment;
        int fileFragmentSize = ntohl(*reinterpret_cast<int*>(puller->pullBytes(sizeof(int))));
        memcpy(&fileFragment, reinterpret_cast<unsigned char*>(puller->pullBytes(fileFragmentSize)), fileFragmentSize);
        fileFragment.size = fileFragmentSize;
        return fileFragment;
    } catch (EndOfBytesException& e) {
        throw EndOfDataException();
    }
}

NodeAddr Deserializer::receiveListiningAddress() {
    NodeAddr addr;
    try{
        addr = *reinterpret_cast<NodeAddr*>(puller->pullBytes(sizeof(NodeAddr)));;
        addr.addr.s_addr=ntohl(addr.addr.s_addr);
        addr.port=ntohs(addr.port);
    } catch (EndOfBytesException& e) {
        throw EndOfDataException();
    }
    return addr;
}
