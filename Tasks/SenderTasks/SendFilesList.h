//
// Created by michal on 23.12.18.
//

#ifndef P2P_SENDFILESLIST_H
#define P2P_SENDFILESLIST_H

#include <vector>
#include <string>
#include "SenderTask.h"
#include "../../OperationCode.h"
#include "../../FileManager.h"

using namespace std;

class SendFilesList: public SenderTask {
public:
    SendFilesList(int taskId, FileManager* fileManager);
    void send(Output* output) override;
private:
    FileManager* fileManager;
};


#endif //P2P_SENDFILESLIST_H
