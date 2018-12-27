//
// Created by michal on 23.12.18.
//

#ifndef P2P_SENDFILESLIST_H
#define P2P_SENDFILESLIST_H

#include <vector>
#include "SenderTask.h"
#include "../../OperationCode.h"

using namespace std;

class SendFilesList: public SenderTask {
public:
    const int operatinoCode = OperationCode::FILES_LIST;
    SendFilesList(int id): SenderTask(id){};
    void send(int) override;
private:
    vector<File> getFilesNames();
};


#endif //P2P_SENDFILESLIST_H
