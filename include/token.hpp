#ifndef TOKEN_H
#define TOKEN_H

#include <vector>
#include <string>
#include <iostream>

namespace Sogolo
{
    enum TokenType {
        TT_FLOAT, 
        TT_INT, 
        TT_STRING, 
        TT_CHAR, 
        TT_SYMBOL,
        
        TT_LPAREN, TT_RPAREN,
        TT_LBRACE, TT_RBRACE,
        TT_LCBRACE, TT_RCBRACE,

        TT_SEMICOLON,
        TT_COMMA
    };

    class Token
    {
    public:
        Token(TokenType t, std::string l, unsigned int ln, std::string v);
        ~Token();

        std::string line;
        unsigned int line_number;
        std::string value;

        TokenType type;
        std::string repr();
    };

    class TokenStream
    {
    private:
        int ptr = 0;
    public:
        TokenStream();
        ~TokenStream();


        std::vector<Token> stream;
        int eof = false;

        void print();
        
        Token next();
        Token peek();
    };
    
    

} // namespace Sogolo


#endif