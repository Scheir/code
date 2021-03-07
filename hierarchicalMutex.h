#include <mutex>
#include <exception>

#pragma once

using namespace std;


// Simple hierarchy mutex class to protect against dead locks.
// If mulitple threads are waiting for locks to be freed its called a dead lock.
// One solution is to have a mutex type like below to protect it from happening.
class hierarchicalMutex
{
private:
    mutex internalMutex;
    unsigned long const hierarchyVal;
    unsigned long prevHierarchyVal;
    static thread_local unsigned long thisThreadHierarchyVal; // thread local is global for current thread
    void checkForHierarchyViolation()
    {
        if(thisThreadHierarchyVal <= hierarchyVal)
        {
            throw logic_error("Mutec hierachy violated");
        }
    }

    void updateHierarchyValue()
    {
        prevHierarchyVal = thisThreadHierarchyVal;
        thisThreadHierarchyVal = hierarchyVal;
    }

public:
    explicit hierarchicalMutex(unsigned long val) : hierarchyVal(val), prevHierarchyVal(0) {}
    void lock()
    {
        checkForHierarchyViolation();
        internalMutex.lock();
        updateHierarchyValue();
    }

    void unlock()
    {
        if(thisThreadHierarchyVal != hierarchyVal)
        {
            throw logic_error("mutex hierarchy violated");
        }
        thisThreadHierarchyVal = prevHierarchyVal;
        internalMutex.unlock();
    }

};

// Initialize it to max value possible
thread_local unsigned long hierarchicalMutex::thisThreadHierarchyVal(ULONG_MAX);
