#include <stack>
#include <mutex>
#include <memory>
#include <exception>

#pragma once
using namespace std;

struct emptyStack : public std::exception
{
    const char* what() const throw()
    {
        return "empty stack";
    }
};

template <typename T>
class threadSafeStack
{
private:
    stack<T> s;
    mutable mutex m;  // mutable variables can mutate in const member methods

public:
    threadSafeStack(){} // default constructor
    threadSafeStack(const threadSafeStack& other) // copy constructor
    {  
        lock_guard<mutex> lock(other.m); // Locking others data for the copying.
        s = other.s;
    }

    threadSafeStack& operator=(const threadSafeStack other)
    {
        lock_guard<mutex> lock(other.m);
        s = other.s;
        return *this;
    }

    void push(T val)
    {
        lock_guard<mutex> lock(m);
        s.push(move(val));
    }

    shared_ptr<T> pop()
    {
        lock_guard<mutex> lock(m);
        if(s.empty())   // Check if empty before pop, throw exception
            throw emptyStack();
        shared_ptr<T> const retPtr {make_shared<T>(s.top())}; //do this before pop to not possibly lose data.
        s.pop();
        return retPtr;  
    }

    void pop(T& value)
    {
        lock_guard<mutex> lock(m);
        if(s.empty())
            throw emptyStack();
        value = s.top();
        s.pop();
    }

    bool empty()
    {
        lock_guard<mutex> lock(m);
        return s.empty();
    }

    T top()
    {
        lock_guard<mutex> lock(m);
        if(s.empty())
            throw emptyStack();
        return s.top();
    }
};