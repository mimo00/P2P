//
// Created by pczyz on 30.12.18.
//

#ifndef P2P_FILEMANAGER_H
#define P2P_FILEMANAGER_H

#include "../OperationCode.h"
#include <vector>
#include <string>


class FileManager {
private:
    string path;
public:
    const string &getPath() const;

public:
    FileManager(string path);
    FileFragment getFile(int hash, int offset);
    vector<File> getFilesNames();
    string getDownloadPath(File file);
    string getStatusPath(File file);
};


#endif //P2P_FILEMANAGER_H
