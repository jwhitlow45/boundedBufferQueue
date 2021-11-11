#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

using namespace std;

class BoundedBufferQueue
{
private:
    int maxQSize;
    queue<int> q;
    mutex mtx;
    condition_variable itemAdded;
    condition_variable itemRemoved;

public:
    BoundedBufferQueue(int qsize) { maxQSize = qsize; }
    void insert(int val);
    int remove();
    void printQueue();
};