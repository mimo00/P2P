//
// Created by pczyz on 07.01.19.
//

#include "FileDownloadManager.h"

#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>

int restOf(File file){
    int a= file.size/OperationCode::PORTION;
    return file.size-(a*OperationCode::PORTION);
}

void saveToFile(FileFragment fragment){
    FILE *fp;
    string dir = "./Files/dwnld";
    string file__ = dir + "/" + fragment.file.name;
    fp = fopen(file__.c_str(), "ab");
    fseek(fp, fragment.offset, SEEK_SET);
    if (fp == nullptr)
        cout << "Error while opening file" << endl;
    else {
        fwrite(fragment.data, sizeof(char), fragment.size, fp);
    }
    fclose(fp);
}
void FileDownloadManager::readFileStatus(int chunks, int* parts){
    string confDir = "./Files/config/config";
    fstream config;
    config.open(confDir,fstream::in | fstream::out| fstream::app);

    if (!config)
        cout << "Error while opening file" << endl;
    else {
        string line;
        while(getline(config, line)) {
            istringstream row(line);
            int isHash;
            row >> isHash;
            if (isHash == filee.hash) {
                for (int i = 0; i < chunks; i++)
                    row >> parts[i];
            }
        }
        config.close();
    }
}
void FileDownloadManager::fileStatus(int chunks,int *parts){
    string confDir = "./Files/config/config";
    fstream config;
    config.open(confDir,fstream::in | fstream::out| fstream::app);
    string conftDir = "./Files/config/configTemp";
    fstream tempConfig;
    tempConfig.open(conftDir, fstream::out | fstream::in | fstream::app);
    if (!config&&!tempConfig)
        cout << "Error while opening file" << endl;
    else {
        /*if (noHash == 0 && zeros > 0) {         //nie znaleziono hasha, uzupelniam plik config
            config << filee.hash;
            for (int j = 0; j < chunks; j++)
                config << " " << parts[j];
        } else {*/
            string line;
            while (getline(config, line)) {
                istringstream row(line);
                int isHash;
                row >> isHash;
                if (isHash != filee.hash) {
                    tempConfig << line<<endl;
                }
            }
            tempConfig << filee.hash;
            for (int j = 0; j < chunks; j++)
                tempConfig << " " << parts[j];
        }
        config.close();
        tempConfig.close();
        remove("./Files/config/config");
        rename("./Files/config/configTemp", "./Files/config/config");
   // }
}

FileDownloadManager::FileDownloadManager(File filee,vector<RemoteNode*> remoteNodes):filee(filee),remoteNodes(remoteNodes) {
}
bool FileDownloadManager::Download(){
    int portionSize = OperationCode::PORTION;
    int chunks;
    if(filee.size%portionSize==0)
        chunks =filee.size/portionSize;
    else
        chunks =filee.size/portionSize+1;

    int *parts= new int[chunks]();
    readFileStatus(chunks,parts);
    int zeros=0;
    int part=0;

    for(int j=0;j<chunks;j++)
        if(parts[j]==0){
            zeros+=1;
        }
    if(zeros==0)
        return false;
    else {
        vector<promise<FileFragment> *> promises(remoteNodes.size());
        vector<FileFragment> fileFrags;
        //int i = 0;
        int toChange[remoteNodes.size()];
        while (zeros > 0&&!remoteNodes.empty()) {
            for (int j = 0; j < remoteNodes.size() && part < filee.size; j++) {
                promises[j] = new promise<FileFragment>;
                for (int d = 0; d < chunks && zeros > 0; d++) {
                    if (parts[d] == 0) {
                        part = d * portionSize;
                        toChange[j] = d;
                        break;
                    }
                }
                remoteNodes[j]->getFileFragment(promises[j], filee, part);
                cout<<"promise wystawiony"<<endl;
                //i++;
            }

            for (int j = 0; j < promises.size(); j++) {
                future<FileFragment> fileFuture = promises[j]->get_future();
                cout<<"future odebrany"<<endl;
                FileFragment tempfrag = fileFuture.get();
                if ((tempfrag.size == portionSize
                     || tempfrag.size == restOf(filee)) && tempfrag.offset == toChange[j] * portionSize) {
                    parts[toChange[j]] = 1;
                    zeros--;
                }
                fileFrags.emplace(fileFrags.begin(), tempfrag);
                delete promises[j];
            }
            fileStatus(chunks,parts);
            for (int j = 0; j < fileFrags.size(); j++) {
                FileFragment fragment = fileFrags.back();
                fileFrags.pop_back();
                saveToFile(fragment);
            }

        }
        delete[] parts;
    return true;
    }
}
FileDownloadManager::~FileDownloadManager() {

}

