//
// Created by michal on 21.12.18.
//

#ifndef P2P_SENDFILESLIST_H
#define P2P_SENDFILESLIST_H


#include "Task.h"
#include "SenderTask.h"

class SendFilesListRequest: public SenderTask {
public:
    int id;
    const int operatinoCode = 100;
    SendFilesListRequest(int id): id(id){};
    Package getPackage() override;
};


#endif //P2P_SENDFILESLIST_H
