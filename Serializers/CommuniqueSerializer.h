//
// Created by michal on 20.12.18.
//

#ifndef P2P_REQUESTSERIALIZER_H
#define P2P_REQUESTSERIALIZER_H


class CommuniqueSerializer {
public:
    CommuniqueSerializer(int socketDescriptor, int operationCode, int taskId);
    void send();

private:
    int socketDescriptor;
    int operationCode;
    int taskId;
};


#endif //P2P_REQUESTSERIALIZER_H
