//
// Created by michal on 21.12.18.
//

#ifndef P2P_SENDERTASK_H
#define P2P_SENDERTASK_H


#include "Task.h"
#include "../Packages/Package.h"

class SenderTask {
public:
    virtual Package getPackage() {};
};


#endif //P2P_SENDERTASK_H
