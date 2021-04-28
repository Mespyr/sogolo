#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include "lexer.hpp"

namespace util {
    struct FileString {   // Hold file content in string
        bool exists;
        Lexer::LexerString str;
    };

    FileString read(std::string filename);
} // namespace util


#endif