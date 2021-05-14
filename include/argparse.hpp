#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <string>
#include <vector>
#include <iostream>

namespace Sogolo 
{
    class ArgumentHolder
    {
    public:
        ArgumentHolder(std::vector<std::string>& argv);
        ~ArgumentHolder();

        std::string filename;
        bool help = false;
        bool none = false;
        bool s_version = false;
        bool debug_tokens = false;
        bool debug_ast = false;
    };
    
} // namespace Sogolo


#endif