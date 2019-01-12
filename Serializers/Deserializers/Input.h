//
// Created by michal on 08.01.19.
//

#ifndef P2P_INPUT_H
#define P2P_INPUT_H

#include <tuple>
#include <vector>
#include "../../Communication/Pullers/Puller.h"
#include "../../OperationCode.h"

using namespace std;

class EndOfDataException : public exception {};

class Input {
public:
    Input(Puller* puller): puller(puller) {}
    virtual bool canRead()=0;
    virtual tuple<int, int> getOperationCodeAndTaskId()=0;
    virtual tuple<int, int> getOffsetAndHash()=0;
    virtual vector<File> receiveFileList()=0;
    virtual vector<NodeAddr> receiveNodeList()=0;
    virtual FileFragment receiveFileFragment()=0;
    virtual NodeAddr receiveListiningAddress()=0;
protected:
    Puller* puller;
};


#endif //P2P_INPUT_H
