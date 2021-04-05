#include "../include/argparse.hpp"

argparse::ArgumentHolder argparse::parse_args(std::vector<std::string> argv)
{
    ArgumentHolder argslots;
    if (argv.size() == 1)
    {
        argslots.none = true;
    }
    else
    {
        for (int i = 1; i < argv.size(); ++i) {
            std::string arg = argv.at(i);
            if ((arg == "-h") || (arg == "--help")) 
            {
                argslots.help = true;
                break;
            } 
            else if ((arg == "-v") || (arg == "--version")) 
            {
                argslots.s_version = true;
                break;
            } 
            else 
            {
                argslots.filename = arg;
                break;
            }
        }
    }
    return argslots;
}