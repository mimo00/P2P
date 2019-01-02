//
// Created by pczyz on 30.12.18.
//

#ifndef P2P_FILEMANAGER_H
#define P2P_FILEMANAGER_H

#include "OperationCode.h"
#include <vector>


class FileManager {
public:
    static vector<File> getFilesNames();
};


#endif //P2P_FILEMANAGER_H
