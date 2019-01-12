//
// Created by pczyz on 28.12.18.
//

#ifndef P2P_SENDFILE_H
#define P2P_SENDFILE_H

#include "SenderTask.h"
#include "../../OperationCode.h"
#include "../../Resources/FileManager.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <sys/types.h>

class SendFile: public SenderTask {
public:
    SendFile(int taskId, int hash, int offset, FileManager* fileManager);
    void send(Output* output) override;
private:
    FileManager* fileManager;
    int hash;
    int offset;
};


#endif //P2P_SENDFILE_H
