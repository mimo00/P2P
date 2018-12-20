//
// Created by michal on 19.12.18.
//

#ifndef P2P_RECEIVEKNOWNNODES_H
#define P2P_RECEIVEKNOWNNODES_H


#include "Task.h"
#include <iostream>

using namespace std;

class ReceiveKnownNodesTask: public Task {
    void execute(){
        cout<< "Wykonuje ReceiveKnownNodesTask"<< endl;
    }
};


#endif //P2P_RECEIVEKNOWNNODES_H
