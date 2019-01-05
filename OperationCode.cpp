//
// Created by michal on 23.12.18.
//

#include "OperationCode.h"

bool NodeAddr::operator==(NodeAddr const &a) {
    return a.port == this->port && a.addr.s_addr==this->addr.s_addr;
}

bool NodeAddr::operator!=(NodeAddr const &a) {
    return !(a.port == this->port && a.addr.s_addr==this->addr.s_addr);
}
