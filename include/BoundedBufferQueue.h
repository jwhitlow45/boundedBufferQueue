#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

using namespace std;

class BoundedBufferQueue
{
private:
    mutex mtx;
    queue<int> q;
    condition_variable itemAdded;
    condition_variable itemRemoved;
public:
    void insert(int val);
    int remove();
    void printQueue();
};