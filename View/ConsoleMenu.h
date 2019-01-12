//
// Created by michal on 29.12.18.
//

#ifndef P2P_CONSOLEMENU_H
#define P2P_CONSOLEMENU_H


#include "../Controllers/Controller.h"

class ConsoleMenu {
public:
    ConsoleMenu(Controller* controller);
    void run();
private:
    Controller* controller;
};


#endif //P2P_CONSOLEMENU_H
