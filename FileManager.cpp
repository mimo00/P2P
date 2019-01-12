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
    string dir="./Files";
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        closedir(dp);
        return files;
    } else {
        while ((dirp = readdir(dp)) != NULL) {
            if(dirp->d_type!=DT_DIR) {
                File file;
                string path=dir+"/"+dirp->d_name;
                strcpy(file.name,dirp->d_name);
                file.size=(int)fsize(path.c_str());
                file.hash=hashFunction(file.name,strlen(file.name),file.size);//rand()%1024;  //zmienic na funcke hashującą
                files.push_back(file);
            }
        }
        closedir(dp);
        return files;
    }
}

string FileManager:: getFilePath(File file) {
    string dir = "./Files";
    return dir + "/" + file.name;
}