//
// Created by pczyz on 07.01.19.
//

#include "FileDownloadManager.h"

#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>


FileDownloadManager::FileDownloadManager(File file, NetworkManager* networkManager, FileManager* fileManager)
        :file(file), networkManager(networkManager), fileManager(fileManager) {
    portionSize = OperationCode::PORTION;
    if(file.size%portionSize==0)
        chunks = file.size/portionSize;
    else
        chunks = file.size/portionSize+1;
    parts= new int[chunks]();
}


void FileDownloadManager::Download(){
    int partIndex;
    int offset;
    if(!getFileStatus())
        fileAlloc();
    while(!downloadFinished()){
        try{
            partIndex = getFirstAvailablePart();
            offset = partIndex*portionSize;
            cout<<"Pobieram paczke "<< partIndex <<endl;
            FileFragment fileFragment = networkManager->getFileFragmentFromRemoteNode(file, offset);
            saveToFile(fileFragment, offset);
            parts[partIndex] = 1;
            updateFileStatus();
        } catch (FileNotAvailableOnNetwork& e){
            cout<<"Nie udalo sie pobrać pliku " << file.name << endl;
            return;
        }
    }
    cout<<"Pobrano plik " << file.name << endl;
}

void FileDownloadManager::updateFileStatus(){
    string conf = fileManager->getStatusPath(file);
    remove(conf.c_str());
    fstream config;
    config.open(conf,fstream::in | fstream::out | fstream::app);
    if (!config)
        cout << "Error while opening status file: " << file.name << endl;
    else {
            for (int i = 0; i < chunks; i++){
                config << parts[i]<<" ";
            }
        config.close();
    }

}

bool FileDownloadManager::getFileStatus(){
    string confDir = fileManager->getStatusPath(file);
    fstream config;
    config.open(confDir,fstream::in | fstream::out | fstream::app);
    if (!config)
        cout << "Error while opening status file: " << file.name << endl;
    else {
        string line;
        getline(config, line);
        istringstream row(line);
        for (int i = 0; i < chunks; i++){
            row >> parts[i];
        }
        config.close();
    }
    for (int i = 0; i < chunks; i++){
        if(parts[i]==1)
            return true;
    }
    return false;

}

void FileDownloadManager::saveToFile(FileFragment fragment, int offset){
    FILE *fp = fopen(fileManager->getDownloadPath(file).c_str(), "rb+");
    if (fp != nullptr){
        fseek(fp, offset, SEEK_SET);
        fwrite(fragment.data, sizeof(char), fragment.size, fp);
        fclose(fp);
    }else
        cout << "Error while opening file1" << endl;
}

void FileDownloadManager::fileAlloc(){
    FILE *fpointer = fopen(fileManager->getDownloadPath(file).c_str(), "a+b");
    auto *buff=new char[file.size]();
    if (fpointer != nullptr){
        fwrite(buff, sizeof(char), file.size, fpointer);
        fclose(fpointer);
    }
    else
        cout << "Error while opening file2" << endl;
}

bool FileDownloadManager::downloadFinished(){
    for (int j = 0; j < chunks; j++)
        if (parts[j] == 0)
            return false;
    return true;
}

int FileDownloadManager::getFirstAvailablePart(){
    for (int d = 0; d < chunks; d++)
        if (parts[d] == 0)
            return d;
}


FileDownloadManager::~FileDownloadManager() {
    updateFileStatus();
    delete parts;
}
