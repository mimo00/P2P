#include <iostream>
#include "RemoteNode.h"
#include "NetworkManager.h"
#include "Tasks/ReceiveKnownNodesTask.h"

#include <set>
#include <thread>
#include <future>
#include <unistd.h>

int main() {
    NetworkManager nm;
    nm.registerRemoteNode(2);
    nm.registerRemoteNode(3);
    sleep(2);
    nm.unregisterRemoteNode(2);
    sleep(2);
    return 0;
}