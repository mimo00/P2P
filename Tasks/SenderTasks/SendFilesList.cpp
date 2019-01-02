//
// Created by michal on 23.12.18.
//

#include "SendFilesList.h"
#include "../../Serializers/CommuniqueSerializer.h"
#include "../../Serializers/FilesListSerializer.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include <string.h>

off_t fsize(const char *filename){
    struct stat st;

    if(lstat(filename,&st)!=0)
        return 0;

    return st.st_size;
}

vector<File> SendFilesList::getFilesNames(){
    vector<File> files;
    srand(time(NULL));
    DIR *dp;
    string dir="/home/michal/Desktop/TIN_TEST"; //to musi być konfigurowalne
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return files;
    } else{
        while ((dirp = readdir(dp)) != NULL) {
            if(dirp->d_type!=DT_DIR) {
                File file;
                string path=dir+"/"+dirp->d_name;
                strcpy(file.name,dirp->d_name);
                file.size=(int)fsize(path.c_str());
                file.hash=rand()%1024;  //zmienic na funcke hashującą
                files.push_back(file);
            }
        }
        closedir(dp);
    }
    return files;
}


void SendFilesList::send(int socket) {
    FilesListSerializer filesListSerializer(socket, operatinoCode, id, getFilesNames());
    filesListSerializer.send();
}

