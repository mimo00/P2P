//
// Created by michal on 20.12.18.
//
#include "Packages/ListOfFilesPackage.h"

#include "RequestSerializer.h"


Package* RequestSerializer::getPackage(){
    Package* package = new ListOfFilesPackage(1, 999);
    return package;
}