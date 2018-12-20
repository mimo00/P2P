//
// Created by michal on 19.12.18.
//

#ifndef P2P_REVEIVER_H
#define P2P_REVEIVER_H

#include <vector>
#include "Stoppable.h"
#include "Tasks/Task.h"

using namespace std;

class Receiver: public Stoppable
{
public:
    vector<Task>* tasks;
    Receiver(vector<Task>* tasks): tasks(tasks){};
    void run()
    {
        std::cout << "Task Start" << std::endl;
        while (!stopRequested())
        {
            std::cout << "Doing Some Work " << tasks->size() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        std::cout << "Task End" << std::endl;
    }
};

#endif //P2P_REVEIVER_H
