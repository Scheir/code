#include <thread>
#include <utility>
#include <iostream>
#pragma once

using namespace std;
class scopedThread
{
    thread t;
public:
    explicit scopedThread(thread t_) : t(move(t_))
    {  
        if(!t.joinable())
        {
            cout << "ERROR: not movable" << endl;
        }
    }

    ~scopedThread()
    {
        cout << "scopedThread destructor" << endl;
        t.join();
    }

    scopedThread(scopedThread const&) = delete;
    scopedThread& operator=(scopedThread const&) = delete;
};