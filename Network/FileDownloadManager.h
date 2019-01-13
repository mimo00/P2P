//
// Created by pczyz on 07.01.19.
//

#ifndef P2P_FILEDOWNLOADMANAGER_H
#define P2P_FILEDOWNLOADMANAGER_H

#include "../OperationCode.h"
#include "RemoteNode.h"
#include "NetworkManager.h"

class FileDownloadManager {
public:
    FileDownloadManager(File file, NetworkManager* networkManager, FileManager* fileManager);
    ~FileDownloadManager();
    void Download();
private:
    File file;
    int portionSize;
    int chunks;
    int *parts;
    FileManager* fileManager;
    NetworkManager* networkManager;
    bool downloadFinished();
    void saveToFile(FileFragment fragment, int offset);
    int getFirstAvailablePart();
    void fileAlloc();
};


#endif //P2P_FILEDOWNLOADMANAGER_H