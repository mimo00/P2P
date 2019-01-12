//
// Created by michal on 27.12.18.
//

#include "ReceiverTask.h"


ReceiverTask::ReceiverTask(int taskId): taskId(taskId){};

int ReceiverTask::getTaskId() const {
    return taskId;
}
