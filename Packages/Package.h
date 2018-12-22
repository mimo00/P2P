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
    Package(int taskId, int operationCode): taskId(taskId), operationCode(operationCode) {};
    int getOperationCode() const { return operationCode; }
    int getTaskId() const { return taskId; }
};


#endif //P2P_PACKAGE_H
