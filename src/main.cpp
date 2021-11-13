//language imports
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

//local imports
#include "utils.cpp"
#include "BoundedBufferQueue.h"

using namespace std;

//function prototypes
void producer(BoundedBufferQueue *BBQ, int threadNum, int sleepRange);
void consumer(BoundedBufferQueue *BBQ, int threadNum, int sleepRange);

const float slowdownThreshold = 0.75;
const int threadPairs = 10;
int itemsProduced = 0;
int itemsConsumed = 0;
int producersHalted = 0;
int consumersHalted = 0;

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
    for (size_t i = 0; i < threadPairs; i++)
    {
        producers.push_back(thread(producer, myBBQ, i, tpSleep));
        consumers.push_back(thread(consumer, myBBQ, i + threadPairs, tcSleep));
    }

    //wait for threads to complete
    //this will never happen but is a low cost way to impose an infinite wait
    while (true)
        ;
    this_thread::sleep_for(chrono::seconds(10));
    cout << "Items produced: " << itemsProduced << endl;
    cout << "Items consumed: " << itemsConsumed << endl;
    cout << "Number of halted producers: " << producersHalted << endl;
    cout << "Number of halted consumers: " << consumersHalted << endl;

    return 0;
}

void producer(BoundedBufferQueue *BBQ, int threadNumber, int sleepRange)
{
    while (true)
    {
        //slow down producing if queue is near full
        //speed up producing if queue is near empty
        int sleepModifier = 1;
        if (BBQ->getQueueCapacity() > slowdownThreshold)
            sleepModifier = 1.0 + (BBQ->getQueueCapacity() - slowdownThreshold) / (1.0 - slowdownThreshold);
        else if (BBQ->getQueueCapacity() < (1 - slowdownThreshold))
            sleepModifier = BBQ->getQueueCapacity() / (1 - slowdownThreshold);
        int sleepTime = (rand() % sleepRange) * sleepModifier;
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
        BBQ->insert(itemsProduced, &threadNumber, &producersHalted);
        itemsProduced++;
        cout << "Item #" << itemsProduced << " produced by thread #" << threadNumber << endl;
    }
}

void consumer(BoundedBufferQueue *BBQ, int threadNumber, int sleepRange)
{
    while (true)
    {
        int sleepTime = rand() % sleepRange;
        this_thread::sleep_for(chrono::milliseconds(sleepTime));
        int item = BBQ->remove(&threadNumber, &consumersHalted);
        itemsConsumed++;
        cout << "Item #" << item << " consumed by thread #" << threadNumber << endl;
    }
}