//
// Created by michal on 08.01.19.
//

#ifndef P2P_DESERIALIZER_H
#define P2P_DESERIALIZER_H


#include "Input.h"


class Deserializer : public Input{
public:
    Deserializer(Puller* puller);
    bool canRead();
    tuple<int, int> getOperationCodeAndTaskId() override;
    tuple<int, int> getOffsetAndHash() override;
    vector<NodeAddr> receiveNodeList() override;
    vector<File> receiveFileList() override;
};


#endif //P2P_DESERIALIZER_H
