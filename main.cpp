#include <iostream>
#include "Network/RemoteNode.h"
#include "Network/NetworkManager.h"
#include "Tasks/SenderTasks/SendFilesList.h"
#include "Tasks/ReceiverTasks/ReceiveFileList.h"
#include "Controllers/Controller.h"
#include "View/ConsoleMenu.h"

#include <set>
#include <cstdlib>
#include <thread>
#include <future>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main(int argc,  char** argv) {
    if (argc != 4 and argc != 6) {
        perror("Give your address or your address and known address\n");
        exit(1);
    }
    srand(time(nullptr));
    NodeAddr myAddr;
    string ip(argv[1]);
    uint16_t port = atoi(argv[2]);
    myAddr.addr.s_addr = inet_addr(ip.c_str());
    myAddr.port = htons(port);
    string path(argv[3]);
    Controller controller(myAddr, path);
    if (argc == 4) {
        try{
            controller.startNewNetwork();
            ConsoleMenu consoleMenu(&controller);
            consoleMenu.run();
        } catch (ControllerException& e){
            cout<<"Cannot start network "<< e.what() << endl;
        }
    }
    else if(argc == 6){
        string knownIp(argv[4]);
        uint16_t knownPort = atoi(argv[5]);
        NodeAddr knownAddr;
        knownAddr.addr.s_addr = inet_addr(ip.c_str());
        knownAddr.port = htons(knownPort);
        controller.connectToNetwork(knownAddr);
        ConsoleMenu consoleMenu(&controller);
        consoleMenu.run();
    };
    return 0;
}
