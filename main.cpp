#include <iostream>
#include "RemoteNode.h"
#include "NetworkManager.h"

#include <set>
#include <thread>
#include <future>
#include <unistd.h>
#include <fcntl.h>

int main() {
//    int descriptor1 = open("/home/michal/Desktop/TIN_TEST/dane1.txt", O_WRONLY);
    int descriptor2 = open("/home/michal/Desktop/TIN_TEST/dane2.txt", O_RDWR);
//    auto rm1 = new RemoteNode(descriptor1);
    auto rm2 = new RemoteNode(descriptor2);
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