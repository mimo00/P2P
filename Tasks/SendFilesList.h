//
// Created by michal on 23.12.18.
//

#ifndef P2P_SENDFILESLIST_H
#define P2P_SENDFILESLIST_H

#include "SenderTask.h"
#include "../OperationCode.h"

class SendFilesList: public SenderTask {
public:
    int id;
    const int operatinoCode = OperationCode::FILES_LIST;
    SendFilesList(int id): id(id){};
    Package getPackage() override;
};


#endif //P2P_SENDFILESLIST_H
