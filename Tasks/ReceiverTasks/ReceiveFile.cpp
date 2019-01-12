//
// Created by pczyz on 29.12.18.
//

#include "ReceiveFile.h"
#include "../../OperationCode.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>


ReceiveFile::ReceiveFile(int id, promise<FileFragment> *fileFragment)
        :ReceiverTask(id),fileFragment(fileFragment){}


void ReceiveFile::handle(int operationCode, Input* input) {
    if (operationCode == OperationCode::DONT_HAVE_FILE){
        FileFragment fileFragment_;
        fileFragment_.size = 0;
        fileFragment->set_value(fileFragment_);
    } else{
        FileFragment fileFragment_ = input->receiveFileFragment();
        fileFragment->set_value(fileFragment_);
    }

}
