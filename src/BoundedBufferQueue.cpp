#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

#include "BoundedBufferQueue.h"

using namespace std;

void BoundedBufferQueue::insert(int val)
{
    return;
}

int BoundedBufferQueue::remove()
{
    return 0;
}

void BoundedBufferQueue::printQueue()
{
    q.push(12);
    q.push(-10);
    q.push(5);
    q.push(2);
    queue<int> pq = q;
    while (!(q.empty()))
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}