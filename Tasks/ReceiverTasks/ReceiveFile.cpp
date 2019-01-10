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


void ReceiveFile::handle(int socket) {
//    FileDeserializer fileDeserializer(socket);
//    int fileSize = fileDeserializer.receiveFileSize();
//    unsigned char buff[OperationCode::PORTION];
//    fileDeserializer.receive(buff, fileSize);
//    FileFragment fileFragment_;
//    fileFragment_.file=file;
//    memcpy(fileFragment_.data, buff, fileSize);
//    fileFragment_.size = fileSize;
//    fileFragment_.offset = offset;
//    fileFragment->set_value(fileFragment_);
}
