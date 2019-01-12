//
// Created by pczyz on 07.01.19.
//

#ifndef P2P_FILEDOWNLOADMANAGER_H
#define P2P_FILEDOWNLOADMANAGER_H

#include "../OperationCode.h"
#include "RemoteNode.h"

class FileDownloadManager {
public:
    FileDownloadManager(File file, RemoteNode* remoteNode, string path);
    ~FileDownloadManager();
    bool Download();
private:
    File file;
    int portionSize;
    int chunks;
    int *parts;
    string path;
    bool downoladFinished();
    void saveToFile(FileFragment fragment, int offset);
    int getFirstAvaiblePart();
        void readFileStatus(int chunks, int* parts);
    void fileStatus(int chunks,int *parts);
    RemoteNode* remoteNode;
};


#endif //P2P_FILEDOWNLOADMANAGER_H