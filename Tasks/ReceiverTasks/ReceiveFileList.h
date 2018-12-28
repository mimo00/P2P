//
// Created by michal on 27.12.18.
//

#ifndef P2P_RECEIVEFILELIST_H
#define P2P_RECEIVEFILELIST_H


#include "ReceiverTask.h"
#include "../../OperationCode.h"

#include <future>
#include <vector>

using namespace std;

class ReceiveFileList : public ReceiverTask{
public:
    ReceiveFileList(int id, promise<vector<File>>* fileNames): ReceiverTask(id), fileNames(fileNames){};
    void handle(int socket) override;
private:
    promise<vector<File>>* fileNames;
};


#endif //P2P_RECEIVEFILELIST_H
