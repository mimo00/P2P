//
// Created by pczyz on 07.01.19.
//

#include "FileDownloadManager.h"

#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>


FileDownloadManager::FileDownloadManager(File file, RemoteNode* remoteNode, string path)
        :file(file), remoteNode(remoteNode), path(path) {
    portionSize = OperationCode::PORTION;
    if(file.size%portionSize==0)
        chunks =(int)file.size/portionSize;
    else
        chunks =(int)file.size/portionSize+1;
    parts= new int[chunks]();
}

size_t restOf(File file){
    auto a= file.size/OperationCode::PORTION;
    return file.size-(a*OperationCode::PORTION);
}

void FileDownloadManager::saveToFile(FileFragment fragment, int offset){
    FILE *fp;
    string dir = path + "./dwnld";
    string file__ = dir + "/" + file.name;
    fp = fopen(file__.c_str(), "rb+");
    //fclose(fp);
    fseek(fp, offset, SEEK_SET);
    //fp = fopen(file__.c_str(), "a+b");
    if (fp == nullptr)
        cout << "Error while opening file" << endl;
    else {
        fwrite(fragment.data, sizeof(char), fragment.size, fp);
    }
    fclose(fp);
}

void fileAlloc(File file){
    FILE *fpointer;
    string dir = "./dwnld";
    string file__ = dir + "/" + file.name;
    fpointer = fopen(file__.c_str(), "a+b");
    char *buff=new char[file.size]();
    //fseek(fp, fragment.offset, SEEK_SET);
    if (fpointer == nullptr)
        cout << "Error while opening file" << endl;
    else {
        fwrite(buff, sizeof(char), file.size, fpointer);
    }
    fclose(fpointer);
}

void FileDownloadManager::fileStatus(int chunks,int *parts){
    string dir = "./status/";
    string file__ = dir + filee.name + to_string(filee.hash);
    fstream config;
    config.open(file__,fstream::in | fstream::out| fstream::app);

    string tempdir= dir +" temp" + filee.name + to_string(filee.hash);
    fstream temp;
    temp.open(tempdir,fstream::in | fstream::out| fstream::app);
    if (!config&&!temp) {
        cout << "Error while opening file" << endl;
    }
    else {

        string line;
        getline(config, line);
        for (int i = 0; i < chunks; i++)
            temp << " " << parts[i];
    }
    config.close();
    temp.close();
    remove(file__.c_str());
    rename(tempdir.c_str(),file__.c_str());
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
        auto fileFragmentPromise = new promise<FileFragment>;
        remoteNode->getFileFragment(fileFragmentPromise, file, offset);
        FileFragment fileFragment = fileFragmentPromise->get_future().get();
        saveToFile(fileFragment, offset);
    }


//    ///////////////
//    for(int j=0;j<chunks;j++)
//        if(parts[j]==0){
//            zeros+=1;
//        }
//    if(zeros==0)
//        return false;
//    else {
//        //int i = 0;
//        if(zeros==chunks)
//            fileAlloc(filee);
//        int toChange[remoteNodes.size()];
//        while (zeros > 0&&!remoteNodes.empty()) {
//            vector<promise<FileFragment> *> promises(remoteNodes.size());
//            vector<FileFragment> fileFrags;
//            for (int j = 0; j < remoteNodes.size() && part < filee.size; j++) {
//                promises[j] = new promise<FileFragment>;
//                for (int d = 0; d < chunks && zeros > 0; d++) {
//                    if (parts[d] == 0) {
//                        part = d * portionSize;
//                        toChange[j] = d;
//                        break;
//                    }
//                }
//                remoteNodes[j]->getFileFragment(promises[j], filee, part);
//                //i++;
//            }
//
//            for (int j = 0; j < remoteNodes.size(); j++) {
//                future<FileFragment> fileFuture = promises[j]->get_future();
//                //fileFuture.is_ready();
//                if(fileFuture.wait_for(chrono::milliseconds(100))==future_status::ready) {
//                    FileFragment tempfrag = fileFuture.get();
//                    if((tempfrag.size == portionSize || tempfrag.size == restOf(filee))
//                       && tempfrag.offset == toChange[j] * portionSize) {
//                        parts[toChange[j]] = 1;
//                        zeros--;
//                        fileFrags.emplace(fileFrags.begin(), tempfrag);
//                        cout<<"spełnia wk"<<endl;
//                    } else
//                        cout<<"NIE SPEŁNIA wk"<<endl;
//
//                    //delete promises[j];
//                } else
//                    cout<<"nie gotowy"<<endl;
//            }
//
//            fileStatus(chunks,parts);
//            //while(!fileFrags.empty()){
//            for (int j = 0; j < fileFrags.size(); j++) {
//                FileFragment fragment = fileFrags.back();
//                fileFrags.pop_back();
//                saveToFile(fragment);
//            }
//
//        }
//        delete[] parts;
//        cout<<"Koniec pobierania"<<endl;
//        return true;
    }
}
FileDownloadManager::~FileDownloadManager() {

}
