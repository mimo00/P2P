//
// Created by michal on 10.01.19.
//

#include "Connector.h"

Connector::Connector(NodeAddr me): me(me){
    lisiningDescriptor = -1;
}

const NodeAddr &Connector::getMe() const {
    return me;
}
