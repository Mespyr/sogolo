#ifndef EDULO_UTILS_H
#define EDULO_UTILS_H

#include <iostream>
#include <fstream>
#include <string>

namespace util
{
    struct FileString
    {
        bool exists;
        std::string str;
    };

    FileString read(std::string filename);    
} // namespace util


#endif