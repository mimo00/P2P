#include <iostream>
#include "RemoteNode.h"
#include "NetworkManager.h"
//#include "Tasks/ReceiveKnownNodesTask.h"

#include <set>
#include <thread>
#include <future>
#include <unistd.h>

int main() {
    RemoteNode* rm1 = new RemoteNode(1);
    RemoteNode* rm2 = new RemoteNode(2);
    NetworkManager nm;
    nm.registerRemoteNode(rm1);
    nm.registerRemoteNode(rm2);
    sleep(2);
    nm.unregisterRemoteNode(rm1);
    sleep(2);
    return 0;
}