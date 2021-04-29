#ifndef LEXER_H
#define LEXER_H

#include "token.hpp"


namespace Lexer {
    class LexerString {
    public:
        std::vector<std::string> lines;
        std::string str;
    };

    class Lexer {
    public: 
        LexerString code;
        Token::TokenStream stream;

        int line_number = 1;
        int idx = -1;

        std::string current_line;
        char current_char;
        bool eof = false;

        void make_string();
        void make_number();
        void make_symbol();
        void skip_comment();

        void advance();
        void tokenize();
    };
} // namespace Lexer

#endif