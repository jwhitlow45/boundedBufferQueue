#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

#include "BoundedBufferQueue.h"

using namespace std;

void BoundedBufferQueue::insert(int val)
{
    unique_lock<mutex> lk(mtx);
    while (q.size() >= maxQSize)
        itemRemoved.wait(lk);
    q.push(val);
    itemAdded.notify_one();
    lk.release();    
}

int BoundedBufferQueue::remove()
{
    int val;
    unique_lock<mutex> lk(mtx);
    while (q.empty())
        itemAdded.wait(lk);
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