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

    BoundedBufferQueue myBBQ(maxQueueSize);




    return 0;
}
