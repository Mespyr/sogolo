#ifndef EDULO_TOKEN_H
#define EDULO_TOKEN_H

#include <vector>
#include <string>
#include <iostream>

namespace Token
{
    class Token
    {
    public:
        std::string line;
        unsigned int line_number;
        std::string value;
        std::string repr();
    };


    class TokenStream
    {
    public:
        std::vector<Token> stream;
        void print();
    };
}

#endif