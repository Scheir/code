#include <thread>
#include <iostream>
#pragma once

using namespace std;

// Using RAII to wait for a thread to complete
class threadGuard
{
    thread& t;
public:
    explicit threadGuard(thread& t_) : t(t_) {}
    ~threadGuard()
    {
        cout << "threadGuard destructor" << endl;
        if(t.joinable())
        {
            t.join();
        }
    }
    threadGuard(threadGuard const&) = delete;
    threadGuard& operator=(threadGuard const&) = delete;
};