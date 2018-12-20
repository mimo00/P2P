//
// Created by michal on 20.12.18.
//

#ifndef P2P_LISTOFFILESPACKAGE_H
#define P2P_LISTOFFILESPACKAGE_H


#include "Package.h"

class ListOfFilesPackage: public Package{
public:
    ListOfFilesPackage(int taskId, int numberOfFiles);
    int getNumberOfFiles();
private:
    int numberOfFiles;
};


#endif //P2P_LISTOFFILESPACKAGE_H
