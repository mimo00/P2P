//
// Created by pczyz on 07.01.19.
//

#ifndef P2P_FILEDOWNLOADMANAGER_H
#define P2P_FILEDOWNLOADMANAGER_H

#include "../OperationCode.h"
#include "RemoteNode.h"

class FileDownloadManager {
public:
    FileDownloadManager(File file, RemoteNode* remoteNode, FileManager* fileManager);
    ~FileDownloadManager();
    bool Download();
private:
    File file;
    int portionSize;
    int chunks;
    int *parts;
    string path;
    FileManager* fileManager;
    bool downoladFinished();
    void saveToFile(FileFragment fragment, int offset);
    int getFirstAvaiblePart();
    void fileAlloc(File file);
    RemoteNode* remoteNode;
};


#endif //P2P_FILEDOWNLOADMANAGER_H