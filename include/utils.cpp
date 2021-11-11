#pragma once
#include <string>
#include <vector>

using namespace std;

int getCommandLineArgument(vector<string> args, string prefix)
{
    for (string arg : args)
    {
        if (arg.size() > prefix.size() + 2 && prefix == arg.substr(1, prefix.size()))
        {
            return stoi(arg.substr(prefix.size() + 2, arg.size() - prefix.size()));
        }
    }
    return -1;
}