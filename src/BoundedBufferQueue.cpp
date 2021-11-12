#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

#include "BoundedBufferQueue.h"

using namespace std;

void BoundedBufferQueue::insert(int val, int *threadNumber)
{
    unique_lock<mutex> lk(mtx);
    while (q.size() >= maxQSize)
    {
        cout << "Waiting to produce by thread number #" << *threadNumber << endl;
        itemRemoved.wait(lk);
    }
    q.push(val);
    itemAdded.notify_one();
    lk.release();
}

int BoundedBufferQueue::remove(int *threadNumber)
{
    int val;
    unique_lock<mutex> lk(mtx);
    while (q.empty())
    {
        cout << "Waiting to consume by thread number #" << *threadNumber << endl;
        itemAdded.wait(lk);
    }
    val = q.front();
    q.pop();
    itemRemoved.notify_one();
    lk.release();
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