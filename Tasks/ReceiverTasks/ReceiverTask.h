//
// Created by michal on 27.12.18.
//

#ifndef P2P_RECEIVERTASK_H
#define P2P_RECEIVERTASK_H


class ReceiverTask {
    public:
        ReceiverTask(int id): id(id){};
        virtual void handle(int socket) = 0;
        int getId() const;

protected:
        int id;
};

#endif //P2P_RECEIVERTASK_H
