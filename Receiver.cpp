//
// Created by michal on 19.12.18.
//

#include "Receiver.h"

using namespace std;

Receiver::Receiver(vector<Task>* tasks): tasks(tasks){};

void Receiver::run()
{
    cout << "Task Start" << endl;
    while (!stopRequested())
    {
        cout << "Doing Some Work " << tasks->size() << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    cout << "Task End" << endl;
}