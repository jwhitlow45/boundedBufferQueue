#include <iostream>
#include <string>
#include <vector>
#include <utils.cpp>

using namespace std;

int main(int argc, char *argv[])
{
    //get command line arguments
    vector<string> args;
    for (size_t i = 0; i < argc; i++)
        args.push_back(string(argv[i]));
    int tpVal = getCommandLineArgument(args, "tp");
    int tcVal = getCommandLineArgument(args, "tc");

    return 0;
}

