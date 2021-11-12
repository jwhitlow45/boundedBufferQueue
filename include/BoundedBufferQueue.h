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
    int getQueueSize() { return q.size(); }
    int getMaxQueueSize() { return maxQSize; }
    void insert(int val, int* threadNumber);
    int remove(int* threadNumber);
    float getQueueCapacity() { return float(getQueueSize() / getMaxQueueSize()); }
    void printQueue();
};