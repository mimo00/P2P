//
// Created by michal on 18.12.18.
//

#ifndef P2P_REMOTENODE_H
#define P2P_REMOTENODE_H

#include <vector>
#include <string>
#include <iostream>

using  namespace std;


class RemoteNode {
public:
    RemoteNode(int sockfd);
    vector <string> get_files();
    int getSockfd()const{ return this->sockfd; }
    bool operator==(const RemoteNode &other);
private:
    int sockfd;
};


#endif //P2P_REMOTENODE_H
