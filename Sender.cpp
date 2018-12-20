//
// Created by pczyz on 20.12.18.
//

#include "Sender.h"
using namespace std;

Sender::Sender(vector<Task> *tasks): tasks(tasks) {};

void Sender::run() {
    cout<<"sender started"<<endl;
    while(!stopRequested())
    {
        cout<<"sender working"<<tasks->size()<<endl;
        this_thread::sleep_for(chrono::milliseconds(2000));
        //cout<<"adding task to receiver list"<<endl;

    }
    cout<<"sender ended";
}