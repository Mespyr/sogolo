#include "argparse.hpp"
namespace Sogolo
{
    ArgumentHolder::ArgumentHolder(std::vector<std::string>& argv)
    {
        if (argv.size() == 1)
            none = true;

        else 
        {
            for (int i = 1; i < argv.size(); ++i) 
            {
                std::string arg = argv.at(i);
                if ((arg == "-h") || (arg == "--help")) 
                {
                    help = true;
                } 
                else if ((arg == "-v") || (arg == "--version")) 
                {
                    s_version = true;
                } 
                else if ((arg == "-t") || (arg == "--read_tokens")) 
                {
                    debug_tokens = true;
                } 
                else if ((arg == "-p") || (arg == "--read_ast")) 
                {
                    debug_ast = true;
                } 
                else 
                {
                    filename = arg;
                    break;
                }
            }
        }
    }
    
    ArgumentHolder::~ArgumentHolder()
    {}
} // namespace Sogolo

