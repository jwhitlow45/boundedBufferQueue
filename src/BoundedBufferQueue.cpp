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
    queue<int> pq = q;
    while (!(q.empty()))
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}