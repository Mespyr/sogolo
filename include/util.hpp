#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include "lexer.hpp"

namespace Sogolo 
{
    // Hold file content in string
    class File
    {
    public:
        File(const std::string& filename);
        ~File();

        bool exists;
        String str;
    };
} // namespace Sogolo


#endif