#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include "threadGuard.h"
#include "scopedThread.h"
#include "paralellAccumulate.h"

using namespace std;

// Passing memberfunction reference and reference to object
// Similiar to std::bind.
class X
{
    public:
    void printSomething(string smtg)
    {
        cout << smtg << endl;
    }
};


// Dangling access to reference Example
// 2.1
void doNothing(int) {};

void countTo(unsigned int count)
{
    for(int i = 0; i < count; i++)
        cout << i << endl;
}

struct funcDanglingReference
{
    int& i;
    funcDanglingReference(int& i_) : i(i_) {}
    void operator() ()
    {
        cout << "Entered funcDanglingReference" << endl;
        for(unsigned int j = 0; j < 10000; j++)
        {
            doNothing(i);
        }
        cout << "exit Dangling Reference" << endl;
    }
};

//2.6
void scopedThreadDanglingReference()
{
    int state = 0;
    scopedThread t{thread(funcDanglingReference(state))};
}

void crashDanglingReference() 
{
    int state = 0;
    funcDanglingReference var(state); // takes reference of state 
    thread t(var);  // run funcDanglingReference
    t.detach();  // thread may still be running
    //t.join();      // Wait for thread to be finnished 
}

void noCrashWithThreadGuard()
{
    int state = 0;
    funcDanglingReference var(state);
    thread t(var);
    threadGuard g(t);

}
// End end Dangling reference example

class BackgroundTask
{
    public:
    void operator()() const
    {
        print("Concurrency!");
    }
    void print(string msg) const
    {
        cout << endl;
        cout << msg << endl;
    }
};

void printNumbers()
{
    for(int i = 0; i < 10; i++)
    {
        cout << i << endl;
    }
}


int main(int, char**) 
{ 

    // Create threads
    // thread t(printNumbers);
    // thread t1 {BackgroundTask()};
    // thread t2 ([]{cout << "Lambda" << endl;});
    // t.join();
    // t1.join();
    // t2.join();
    
    // X obj;
    // thread t3{&X::printSomething, &obj, "print something"};
    // t3.join();

    // Dangling reference example
    //crashDanglingReference();
    // noCrashWithThreadGuard();
    
    // 2.6
    // scopedThreadDanglingReference();

    // 2.8
    // vector<thread> threads;
    // for(size_t i = 0; i < 5; i++)
    // {
    //     threads.emplace_back(countTo, 5);
    // }
    // for(auto& ele : threads)
    //     ele.join();

    // Test parallelAccumulate
    vector<int> v(100000,1);
    cout << paralellAccumulate(v.begin(), v.end(), 0) << endl;


    cout << "end of program" << endl;
}
