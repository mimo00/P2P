//
// Created by pczyz on 07.01.19.
//

#include "FileDownloadManager.h"

#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>


FileDownloadManager::FileDownloadManager(File file, RemoteNode* remoteNode, FileManager* fileManager)
        :file(file), remoteNode(remoteNode), fileManager(fileManager) {
    path = fileManager->getPath();
    portionSize = OperationCode::PORTION;
    if(file.size%portionSize==0)
        chunks = file.size/portionSize;
    else
        chunks = file.size/portionSize+1;
    parts= new int[chunks]();
}


void FileDownloadManager::saveToFile(FileFragment fragment, int offset){
    FILE *fp;
    string dir = path + "/dwnld";
    string file__ = dir + "/" + file.name;
    fp = fopen(file__.c_str(), "rb+");
    if (fp == nullptr)
        cout << "Error while opening file1" << endl;
    else {
        fseek(fp, offset, SEEK_SET);
        fwrite(fragment.data, sizeof(char), fragment.size, fp);
    }
    fclose(fp);
}

void FileDownloadManager::fileAlloc(File file){
    string dir = path + "/dwnld";
    string file__ = dir + "/" + file.name;
    FILE *fpointer = fopen(file__.c_str(), "a+b");
    char *buff=new char[file.size]();
    if (fpointer != nullptr)
        fwrite(buff, sizeof(char), file.size, fpointer);
    else
        cout << "Error while opening file2" << endl;
    fclose(fpointer);
}

bool FileDownloadManager::downoladFinished(){
    for (int j = 0; j < chunks; j++)
        if (parts[j] == 0)
            return false;
    return true;
}

int FileDownloadManager::getFirstAvaiblePart(){
    for (int d = 0; d < chunks; d++)
        if (parts[d] == 0)
            return d;
}


bool FileDownloadManager::Download(){
    fileAlloc(file);
    while(!downoladFinished()){
        int partIndex = getFirstAvaiblePart();
        int offset = partIndex*portionSize;
        cout<<"Pobieram paczke "<< partIndex <<endl;
        auto fileFragmentPromise = new promise<FileFragment>;
        remoteNode->getFileFragment(fileFragmentPromise, file, offset);
        FileFragment fileFragment = fileFragmentPromise->get_future().get();
        saveToFile(fileFragment, offset);
        parts[partIndex] = 1;
    }
}

FileDownloadManager::~FileDownloadManager() {

}
