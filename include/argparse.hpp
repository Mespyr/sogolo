#ifndef EDULO_ARGPARSE_H
#define EDULO_ARGPARSE_H

#include <string>
#include <vector>
#include <iostream>

namespace argparse
{
    class ArgumentHolder
    {
    public:
        std::string filename;
        bool help = false;
        bool none = false;
        bool s_version = false;
    };
    ArgumentHolder parse_args(std::vector<std::string> argv);
} // namespace argparse


#endif