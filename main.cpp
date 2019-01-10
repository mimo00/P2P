#include <iostream>
#include "Network/RemoteNode.h"
#include "Network/NetworkManager.h"
#include "Tasks/SenderTasks/SendFilesList.h"
#include "Tasks/ReceiverTasks/ReceiveFileList.h"
#include "Controller.h"
#include "ConsoleMenu.h"

#include <set>
#include <cstdlib>
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
    srand(time(nullptr));
    NodeAddr myAddr;
    string ip(argv[1]);
    uint16_t port = atoi(argv[2]);
    myAddr.addr.s_addr = inet_addr(ip.c_str());
    myAddr.port = htons(port);
    Controller controller(myAddr);
    if (argc == 3) {
        try{
            controller.startNewNetwork();
            ConsoleMenu consoleMenu(&controller);
            consoleMenu.run();
        } catch (ControllerException& e){
            cout<<"Cannot start network "<< e.what() << endl;
        }
    }
    else if(argc == 5){
        string knownIp(argv[3]);
        uint16_t knownPort = atoi(argv[4]);
        NodeAddr knownAddr;
        knownAddr.addr.s_addr = inet_addr(ip.c_str());
        knownAddr.port = htons(knownPort);
        controller.connectToNetwork(knownAddr);
        ConsoleMenu consoleMenu(&controller);
        consoleMenu.run();
    };
    return 0;
}
