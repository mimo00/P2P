//
// Created by michal on 18.12.18.
//

#include "RemoteNode.h"

#include <thread>
#include <future>
#include <unistd.h>


void initiazer(promise<vector<string>> *promObj)
{
    vector<string> a;
    a.emplace_back("a");
    a.emplace_back("ab");
    a.emplace_back("abc");
    sleep(1);
    promObj->set_value(a);
    return;
}


RemoteNode::RemoteNode(int sockfd): sockfd(sockfd){}


vector<string> RemoteNode::get_files(){
    promise<vector<string>> promiseObj;
    future<vector<string>> futureObj = promiseObj.get_future();
    thread th(initiazer, &promiseObj);
    vector<string> fileList = futureObj.get();
    th.detach();
    return fileList;
}

bool RemoteNode::operator==(const RemoteNode &other){
    return this->getSockfd() == other.getSockfd();
}