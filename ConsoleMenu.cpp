//
// Created by michal on 29.12.18.
//

#include "ConsoleMenu.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

ConsoleMenu::ConsoleMenu(Controller * controller): controller(controller) {}

void ConsoleMenu::run() {
    while(true){
        cout << "1 - Dostepny wezly." << endl;
        cout << "exit - wyjscie." << endl;
        string line;
        getline(cin, line);
        //system("clear");
        if (line == "1"){
            cout<<"Liczba dostepnych wezlow: " << controller->getNodesAddresses().size() << endl;
            for(int i=0;i<controller->getNodesAddresses().size(); i++){
                NodeAddr node = controller->getNodesAddresses().at(i);
                cout << inet_ntoa(node.addr) << "    " << ntohs(node.port) << endl;
            }
        }
        if (line == "exit"){
            return;
        }

    }
}
