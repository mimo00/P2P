//
// Created by michal on 20.12.18.
//

#ifndef P2P_PACKAGE_H
#define P2P_PACKAGE_H


class Package {
protected:
    int operationCode;
    int taskId;
    void* data;
    int numberOfRows;
public:
    Package(int taskId, int operationCode);
    Package(int taskId, int operationCode, void* data, int numberOfRows);
    int getOperationCode() const { return operationCode; }
    int getTaskId() const { return taskId; }
    void *getData() const;
    int getNumberOfRows() const;
    bool hasData();
};


#endif //P2P_PACKAGE_H
