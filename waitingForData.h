#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <condition_variable>
#include <unistd.h>

using namespace std;

#pragma once

namespace WD
{

mutex mut;
queue<int> dataQueue;
condition_variable cond;
extern vector<int> lotsOfData;
vector<int> processedData;

bool dataLeft()
{
    cout << "dataLeft to process: " << lotsOfData.size() << endl;
    return WD::lotsOfData.size() == 0 ? false : true;
}

void processData(int data)
{
    // Do someting cool and time consuming
    processedData.push_back(data + 5);
}

vector<int> prepareData()
{
    // Do something cool and time consuming/computer heavy
    cout << "prepare data" << endl;
    sleep(3);
    if(lotsOfData.size() > 5)
    {
        vector<int> tempVec(lotsOfData.begin(), lotsOfData.begin()+5);
        lotsOfData.erase(lotsOfData.begin(), lotsOfData.begin()+5);
        return tempVec;
    }
    else
    {
        vector<int> tempVec(lotsOfData);
        lotsOfData.erase(lotsOfData.begin(), lotsOfData.end());
        return tempVec;
    }
}

void prepDataThread()
{
    while(dataLeft())
    {
        vector<int> temp = prepareData();
        {
            lock_guard<mutex> lk(mut);
            for(auto x : temp)
                dataQueue.push(x);
            cout << "data prepared" << endl;
        }
        cond.notify_one();
    }
}

void dataProcessingThread()
{
    for(;;)
    {
        unique_lock<mutex> lk(mut);
        cond.wait(lk, [](){return !dataQueue.empty();});
        int tempData = dataQueue.front();
        dataQueue.pop();
        lk.unlock();
        processData(tempData);
        cout << "data Processed! Elements left in chunk: " << dataQueue.size() << endl;
        if(dataQueue.empty() && !dataLeft())
            break;
    }
}

void printOne()
{
    cout << "val of elements: " << processedData[0] << ", size processed data vec: " << processedData.size() << endl;
}

}