//
// Created by pczyz on 30.12.18.
//

#include "FileManager.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

FileManager::FileManager(string path) : path(path) {}

FileFragment FileManager::getFile(int hash, int offset) {
    FileFragment fileFragment;
    fileFragment.size = -1;
    vector<File> files=FileManager::getFilesNames();
    for(int i=0; i<files.size();i++) {
        if (files.at(i).hash == hash) {
            FILE *file;
            string filePath = path + "/" + files.at(i).name;
            file = fopen(filePath.c_str(), "rb");
            fseek(file,offset,SEEK_SET);
            ssize_t nread = fread(fileFragment.data, sizeof(char), OperationCode::PORTION, file);
            fileFragment.size = (int)nread;
            fclose(file);
        }
    }
    return fileFragment;
}


off_t fsize(const char *filename){
    struct stat st;
    if(lstat(filename,&st)!=0)
        return 0;

    return st.st_size;
}

int hashFunction(char name[],int nameSize,int size){
    int hash=0;
    for(int i=0; i<nameSize;i++)
        hash=hash+(int)name[i];
    hash+=size;
    return hash;
}


vector<File> FileManager:: getFilesNames(){
    vector<File> files;
    DIR *dp;
    string dir=path;
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == nullptr) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        closedir(dp);
        return files;
    } else {
        while ((dirp = readdir(dp)) != nullptr) {
            if(dirp->d_type!=DT_DIR) {
                File file;
                string path=dir+"/"+dirp->d_name;
                strcpy(file.name,dirp->d_name);
                file.size=(int)fsize(path.c_str());
                file.hash=hashFunction(file.name, strlen(file.name),file.size);//rand()%1024;  //zmienic na funcke hashującą
                files.push_back(file);
            }
        }
        closedir(dp);
        return files;
    }
}

const string &FileManager::getPath() const {
    return path;
}

string FileManager::getDownloadPath(File file) {
    string downloadPath = path + "/dwnld";
    string filePath = downloadPath + "/" + file.name;
    return filePath;
}

string FileManager::getStatusPath(File file) {
    string statusPath = path + "/status";
    string filePath = statusPath + "/" + to_string(file.hash) +"("+file.name+")";
    return filePath;
}