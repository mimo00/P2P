//
// Created by michal on 23.12.18.
//

#ifndef P2P_OPERATIONCODE_H
#define P2P_OPERATIONCODE_H


#include <zconf.h>
#include <netinet/in.h>
#include <list>
#include <algorithm>

using namespace std;

class OperationCode {
public:
    const static int NODES_LIST_REQUEST = 102;
    const static int NODES_LIST = 103;
    const static int FILES_LIST_REQUEST = 300;
    const static int FILES_LIST = 302;
    const static int FILE_FRAGMENT_REQUEST=400;
    const static int DONT_HAVE_FILE=402;
    const static int FILE_FRAGMENT=403;


    const static int PORTION=1048576;
    static bool isRequest(int operationCode){
        const list<int> requestOperationCodes = list<int>({
            FILES_LIST_REQUEST,
            NODES_LIST_REQUEST,
            FILE_FRAGMENT_REQUEST
        });
        return find(requestOperationCodes.begin(), requestOperationCodes.end(), operationCode) != requestOperationCodes.end();
    }

};


struct File {
    char name[64];
    int hash;
    int size;
};

struct FileFragment {
    File file;
    unsigned char data[OperationCode::PORTION];
};

struct NodeAddr{
    in_addr addr;
    in_port_t port;
};

#endif //P2P_OPERATIONCODE_H
