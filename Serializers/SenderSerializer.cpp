//
// Created by michal on 20.12.18.
//
#include "../Packages/ListOfFilesPackage.h"

#include "SenderSerializer.h"
#include <iostream>

using namespace std;

void SenderSerializer::send(Package package){
    cout<<"Wysylam pakiet "<< package.getTaskId() << " " << package.getOperationCode() << endl;
}