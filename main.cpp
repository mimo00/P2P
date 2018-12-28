#include <iostream>
#include "RemoteNode.h"
#include "NetworkManager.h"

#include "Tasks/SenderTasks/SendFilesList.h"
#include <vector>

#include <set>
#include <thread>
#include <future>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int descriptor1 = open("./dane/dane1.txt", O_RDWR);
    int descriptor2 = open("./dane/dane2.txt", O_RDWR);
//    auto rm1 = new RemoteNode(descriptor1);
    auto rm2 = new RemoteNode(descriptor2);
    //rm2->getFilesList();
    //auto test = new SendFilesList(10);
    //test->send(descriptor1);
//    NetworkManager nm;
//    nm.registerRemoteNode(rm1);
//    nm.registerRemoteNode(rm2);
//    rm1->getFilesList();
    sleep(120);
//    rm1->getFilesList();
//    nm.unregisterRemoteNode(rm1);
    sleep(2);
    return 0;
}