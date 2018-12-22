#include <iostream>
#include "RemoteNode.h"
#include "NetworkManager.h"
//#include "Tasks/ReceiveKnownNodesTask.h"

#include <set>
#include <thread>
#include <future>
#include <unistd.h>

int main() {
    auto rm1 = new RemoteNode(1);
//    auto rm2 = new RemoteNode(2);
    NetworkManager nm;
    nm.registerRemoteNode(rm1);
//    nm.registerRemoteNode(rm2);
    rm1->getFilesList();
    sleep(3);
    rm1->getFilesList();
    nm.unregisterRemoteNode(rm1);
    sleep(2);
    return 0;
}