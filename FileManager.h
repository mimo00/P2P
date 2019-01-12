//
// Created by pczyz on 30.12.18.
//

#ifndef P2P_FILEMANAGER_H
#define P2P_FILEMANAGER_H

#include "OperationCode.h"
#include <vector>
#include <string>


class FileManager {
public:
    static FileFragment getFile(string path, int hash, int offset);
    static vector<File> getFilesNames(string path);
    static string getFilePath(File file);
};


#endif //P2P_FILEMANAGER_H
