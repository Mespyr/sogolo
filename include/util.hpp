#ifndef FENNEC_UTILS_H
#define FENNEC_UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include "lexer.hpp"

namespace util
{
    struct FileString
    {
        bool exists;
        Lexer::LexerString str;
    };

    FileString read(std::string filename);    
} // namespace util


#endif