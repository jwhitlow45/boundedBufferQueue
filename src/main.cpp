#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getCommandLineArgument(vector<string>, string);

int main(int argc, char *argv[])
{
    //get command line arguments
    vector<string> args;
    for (size_t i = 0; i < argc; i++)
        args.push_back(string(argv[i]));
    int tpVal = getCommandLineArgument(args, "tp");
    int tcVal = getCommandLineArgument(args, "tc");

    cout << tpVal << " " << tcVal << endl;

    return 0;
}

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