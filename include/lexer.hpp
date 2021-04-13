#ifndef FENNEC_LEXER_H
#define FENNEC_LEXER_H

#include "token.hpp"


namespace Lexer
{
    class LexerString
    {
    public:
        std::vector<std::string> lines;
        std::string str;
    };

    class Lexer
    {
    public: 
        LexerString code;
        Token::TokenStream stream;
        void tokenize();
    };

    bool is_important_char(char c);
}

#endif