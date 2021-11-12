#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

#include "BoundedBufferQueue.h"

using namespace std;

void BoundedBufferQueue::insert(int val, int *threadNumber, int *producersHalted)
{
    unique_lock<mutex> lk(mtx);
    while (q.size() >= maxQSize)
    {
        cout << "Waiting to produce by thread number #" << *threadNumber << endl;
        (*producersHalted)++;
        itemRemoved.wait(lk);
    }
    q.push(val);
    itemAdded.notify_one();
    lk.unlock();
}

int BoundedBufferQueue::remove(int *threadNumber, int *consumersHalted)
{
    int val;
    unique_lock<mutex> lk(mtx);
    while (q.empty())
    {
        cout << "Waiting to consume by thread number #" << *threadNumber << endl;
        (*consumersHalted)++;
        itemAdded.wait(lk);
    }
    val = q.front();
    q.pop();
    itemRemoved.notify_one();
    lk.unlock();
    return val;
}

void BoundedBufferQueue::printQueue()
{
    queue<int> pq = q;
    while (!(q.empty()))
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}