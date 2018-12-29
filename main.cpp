#include <iostream>
#include "RemoteNode.h"
#include "NetworkManager.h"
#include "Tasks/SenderTasks/SendFilesList.h"
#include "Tasks/ReceiverTasks/ReceiveFileList.h"
#include "Controller.h"
#include "ConsoleMenu.h"

#include <set>
#include <thread>
#include <future>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main(int argc,  char** argv) {
    if (argc != 3 and argc != 5) {
        perror("Give your address or your address and known address\n");
        exit(1);
    }
    NodeAddr myAddr;
    string ip(argv[1]);
    uint16_t port = atoi(argv[2]);
    myAddr.addr.s_addr = inet_addr(ip.c_str());
    myAddr.port = htons(port);
    Controller controller;
    if (argc == 3) {
        controller.startNewNetwork(myAddr);
    }else if(argc == 5){
        string knownIp(argv[3]);
        uint16_t knownPort = atoi(argv[4]);
        NodeAddr knownAddr;
        knownAddr.addr.s_addr = inet_addr(ip.c_str());
        knownAddr.port = htons(knownPort);
        controller.connectToNetwork(myAddr, knownAddr);
    }
    ConsoleMenu consoleMenu(&controller);
    consoleMenu.run();
    return 0;
}
