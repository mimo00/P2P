//
// Created by michal on 08.01.19.
//

#include <iostream>
#include "Input.h"

Input::Input(Puller* puller): puller(puller) {};

Input::~Input(){
    delete puller;
}