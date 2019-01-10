//
// Created by michal on 29.12.18.
//

#include "ConsoleMenu.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <fstream>
#include <string>
#include <sstream>
ConsoleMenu::ConsoleMenu(Controller * controller): controller(controller) {}

void ConsoleMenu::run() {
    while(true){
        cout<<"MENU"<<endl;
        cout << "1 - Dostepny wezly." << endl;
        cout << "2 - Dostepne pliki w sieci" << endl;
        cout << "3 - Pobierz plik" << endl;
        cout << "exit - wyjscie." << endl;
        string line;
        getline(cin, line);
       // switch(line):
        //system("clear");
        if (line == "1"){
       // case 1:
            cout<<"Liczba dostepnych wezlow: " << controller->getNodesAddresses().size() << endl;
            for(int i=0;i<controller->getNodesAddresses().size(); i++){
                NodeAddr node = controller->getNodesAddresses().at(i);
                cout << inet_ntoa(node.addr) << "    " << ntohs(node.port) << endl;
            }
        }
        else if (line == "2"){
            vector<File> files = controller->getFiles();
            cout<<"Liczba dostepnych plikow w sieci: " << files.size() << endl;
            cout<<"Name"<< "    "<<"Size"<< endl;
            for(int i=0;i<files.size(); i++){
                File file = files.at(i);
                cout << file.name << "    " << file.size << endl;
            }
        }
        else if (line == "3") {
            vector<File> files = controller->getFiles();
            int choice;
            cout << "Wybierz numer pliku do pobrania" << endl;
            cout << "Number" << "    " << "Name" << "    " << "Size" << endl;
            for (int i = 1; i <= files.size(); i++) {
                File file = files.at(i-1);
                cout << i << " - " << file.name << "    " << file.size << endl;
            }
            cout << 0 << " - powrót"<<endl;

            cin >> choice;
            File choosenFile;
            if (choice != 0){
                for (int i = 1; i <= files.size(); i++) {
                    if (choice == i)
                        File choosenFile = files.at(i-1);
                }
                controller->downloadFile(choosenFile);
                }
        }

        else if(line == "exit"){
            return;
        }
        /*else {
           cout<<"Wybierz ponownie poprawną opcję"<<endl;
        }*/

    }
}
