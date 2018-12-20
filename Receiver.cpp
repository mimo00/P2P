//
// Created by michal on 19.12.18.
//

#include "Receiver.h"
#include "RequestSerializer.h"
#include "Packages/ListOfFilesPackage.h"

using namespace std;

Receiver::Receiver(vector<Task>* tasks): tasks(tasks){};

void Receiver::run()
{
    cout << "Start Receiver" << endl;
    RequestSerializer requestSerializer;
    while (!stopRequested())
    {
        Package* package = requestSerializer.getPackage();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    cout << "Task End" << endl;
}