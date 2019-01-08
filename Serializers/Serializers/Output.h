//
// Created by michal on 08.01.19.
//

#ifndef P2P_OUTPUT_H
#define P2P_OUTPUT_H


#include <vector>
#include "../../Communication/Pushers/Pusher.h"
#include "../../OperationCode.h"

class Output {
public:
    Output(Pusher* pusher): pusher(pusher) {}
    virtual void requestForNodeList(int taskId)=0;
    virtual void requestForFileList(int taskId)=0;
    virtual void sendNodesList(int taskId, vector<NodeAddr> addresses)=0;
    virtual void sendFileList(int taskId, vector<File> files)=0;

protected:
    Pusher* pusher;
};


#endif //P2P_OUTPUT_H
