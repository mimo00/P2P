//
// Created by michal on 20.12.18.
//

#ifndef P2P_REQUESTSERIALIZER_H
#define P2P_REQUESTSERIALIZER_H


class CommuniqueSerializer {
public:
    CommuniqueSerializer(int socketDescriptor, int operationCode, int taskId);
    CommuniqueSerializer(int socketDescriptor, int operationCode, int taskId, int offset, int hash);
    void send();
    void sendFileReq();

private:
    int socketDescriptor;
    int operationCode;
    int taskId;
    int offset;
    int hash;
};


#endif //P2P_REQUESTSERIALIZER_H
