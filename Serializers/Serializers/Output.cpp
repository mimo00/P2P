//
// Created by michal on 08.01.19.
//

#include <iostream>
#include "Output.h"

Output::Output(Pusher* pusher): pusher(pusher) {}

Output::~Output() {
    delete pusher;
}
