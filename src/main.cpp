//language imports
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

//local imports
#include "utils.cpp"
#include "BoundedBufferQueue.h"

using namespace std;

//function prototypes
void producer(BoundedBufferQueue *BBQ, int *threadNum, int *sleepRange);
void consumer(BoundedBufferQueue *BBQ, int *threadNum, int *sleepRange);

int main(int argc, char *argv[])
{
    //seed rng
    srand(time(NULL));
    // //get command line arguments
    vector<string> args;
    for (size_t i = 0; i < argc; i++)
        args.push_back(string(argv[i]));
    int tpSleep = getCommandLineArgument(args, "tp");
    int tcSleep = getCommandLineArgument(args, "tc");
    int maxQueueSize = getCommandLineArgument(args, "qs");
    //default queue size to 25
    maxQueueSize = maxQueueSize == -1 ? 25 : maxQueueSize;

    BoundedBufferQueue *myBBQ = new BoundedBufferQueue(maxQueueSize);

    //create producers and consumers (0-9 are produvers, 10-19 are consumers)
    vector<thread> producers;
    vector<thread> consumers;

    return 0;
}

void consumer(BoundedBufferQueue *BBQ, int *threadNum, int *sleepRange)
{
    while (true)
    {
        int sleepTime = rand() % *sleepRange;
        int item = BBQ->remove();
        cout << "Item #" << item << " consumed by thread #" << threadNum << endl;
    }
}

void producer(BoundedBufferQueue *BBQ, int *threadNum, int *sleepRange)
{
    while (true)
    {
        int sleepTime = rand() % *sleepRange;
        int item = rand()%1000000;
        BBQ->insert(item);
        cout << "Item #" << item << " produced by thread #" << threadNum << endl;
    }
}