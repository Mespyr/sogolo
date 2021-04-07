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
    private:
        int ptr = 0;
    public:
        std::vector<Token> stream;
        int eof = false;

        void print();
        Token next();
        Token peek();
    };
}

#endif