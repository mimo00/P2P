//
// Created by pczyz on 07.01.19.
//

#ifndef P2P_FILEDOWNLOADMANAGER_H
#define P2P_FILEDOWNLOADMANAGER_H

#include "OperationCode.h"
#include "RemoteNode.h"

class FileDownloadManager {
public:
    FileDownloadManager(File file,vector<RemoteNode*> remoteNodes);
    ~FileDownloadManager();
    bool Download();
private:
    File filee;
    void readFileStatus(int chunks, int* parts);
    void fileStatus(int chunks,int *parts);
    vector<RemoteNode*> remoteNodes;
};


#endif //P2P_FILEDOWNLOADMANAGER_H
