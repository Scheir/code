#include <thread>
#include <stdlib.h>
#include <numeric>
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>

#pragma once
using namespace std;


// This function object will accumulate one block 
// of the vector, each thread gets its own block to process.
template<typename Iterator, typename T>
struct accumulateBlock
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = accumulate(first,last, result);
    }
};

// Similiar signature as std::accumulate.
// Call with vec.begin(), vec.end(), initial value.
template<typename Iterator, typename T>
T paralellAccumulate(Iterator first, Iterator last, T init)
{
    // size of vector
    unsigned long const length = std::distance(first, last);

    // Empty vector case
    if(!length)
        return init;

    // Calculate atleast 25 elements per
    unsigned long const minPerThread = 25;
    
    // Calculate how many threads to use. If vector is small it will
    // be decided by maxthreads, otherwise, hardware_concurrency
    // will decide number of the threads https://en.cppreference.com/w/cpp/thread/thread/hardware_concurrency
    unsigned long const maxThreads = (length + minPerThread - 1) / minPerThread;
    unsigned long const hardwareThreads = thread::hardware_concurrency();
    //cout << "hardware Threads in your system: " << hardwareThreads << endl; Uncomment to see cores in hardware
    unsigned long const numThreads = 
        min(hardwareThreads != 0 ? hardwareThreads : 2, maxThreads);

    // Elemets to process per thread 
    unsigned long const blockSize = length / numThreads;

    vector<T> results(numThreads);
    vector<thread> threads;
    Iterator blockStart = first;

    for(int i = 0; i < numThreads-1; i++)
    {
        Iterator blockEnd = blockStart;
        advance(blockEnd, blockSize); // Iterator addition, move iterator by blocksize
        // Launch a thread and start calculation of block
        threads.emplace_back(accumulateBlock<Iterator,T>(), blockStart, blockEnd, ref(results[i]));
        blockStart = blockEnd;
    }

    // join all new threads to the master thread
    for(auto& ele : threads)
    {
        if(ele.joinable())
        ele.join();
    }

    // If threre are elements left in the vector, calculate and add to last element in result.
    accumulateBlock<Iterator,T>()(blockStart, last, results[numThreads-1]);
    return accumulate(results.begin(), results.end(), init);
}