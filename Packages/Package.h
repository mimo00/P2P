//
// Created by michal on 20.12.18.
//

#ifndef P2P_PACKAGE_H
#define P2P_PACKAGE_H


class Package {
protected:
    int operationCode;
    int taskId;
public:
    Package(int taskId): taskId(taskId) {};
    int getTaskId() {return taskId;};
};


#endif //P2P_PACKAGE_H
