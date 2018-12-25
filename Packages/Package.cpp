//
// Created by michal on 20.12.18.
//

#include "Package.h"

Package::Package(int taskId, int operationCode)
        : taskId(taskId), operationCode(operationCode) {
    data = nullptr;
    numberOfRows = 0;
};

Package::Package(int taskId, int operationCode, void* data, int numberOfRows)
: taskId(taskId), operationCode(operationCode), data(data), numberOfRows(numberOfRows) {};


bool Package::hasData(){
    return data != nullptr;
}

void *Package::getData() const {
    return data;
}

int Package::getNumberOfRows() const {
    return numberOfRows;
}
