#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>

#include "token.hpp"
#include "errors.hpp"

namespace Sogolo 
{
    class String
    {
    public:
        std::vector<std::string> lines;
        std::string str;
    };

    class Lexer
    {
    public:
        Lexer(String c);
        ~Lexer();

        String code;
        TokenStream stream;

        int line_number = 1;
        int idx = -1;

        std::string current_line;
        char current_char;
        bool eof = false;
        bool in_comment = false;

        // Error
        bool error_found = false;
        Error error;

        std::string em;

        // Make objects
        void make_string();
        void make_number();
        void make_symbol();

        void advance();
        void stepdown();

        void tokenize();


    };
    

} // namespace Sogolo

#endif