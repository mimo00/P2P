//
// Created by michal on 23.12.18.
//

#ifndef P2P_OPERATIONCODE_H
#define P2P_OPERATIONCODE_H


class OperationCode {
public:
    const static int FILES_LIST_REQUEST = 300;
    const static int FILES_LIST = 302;
};


struct File {
    char name[64];
    int hash;
    int size;
};
#endif //P2P_OPERATIONCODE_H
