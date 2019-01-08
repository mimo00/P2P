//
// Created by michal on 08.01.19.
//

#ifndef P2P_SERIALIZER_H
#define P2P_SERIALIZER_H


#include <vector>
#include "Output.h"
#include "../../OperationCode.h"

class Serializer: public Output {
public:
    Serializer(Pusher* pusher);
    void requestForNodeList(int taskId) override;
    void requestForFileList(int taskId) override;
    void sendNodesList(int taskId, vector<NodeAddr> addresses) override;
    void sendFileList(int taskId, vector<File> files) override;
};


#endif //P2P_SERIALIZER_H
