//
// Created by michal on 28.12.18.
//

#ifndef P2P_LISTENER_H
#define P2P_LISTENER_H


#include "Stoppable.h"
#include "NetworkManager.h"


class Listener: public Stoppable {
public:
    Listener(NetworkManager* networkManager);
    void run();
private:
    NetworkManager* networkManager;
};

class ListenerException : public exception {};


#endif //P2P_LISTENER_H
