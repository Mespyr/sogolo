#include "token.hpp"

namespace Sogolo
{
    // Token
    Token::Token(TokenType t, const std::string l, unsigned int ln, const std::string v)
    {
        type = t;
        line = l;
        line_number = ln;
        value = v;
    }
    
    Token::~Token()
    {}

    // String Representation of token
    std::string Token::repr() {
        std::string rep;
        rep += "Token:\n";
        rep += "\tValue: '" + value + "'\n";
        rep += "\tLine: '" + line + "'\n";
        rep += "\tLine Number: " + std::to_string(line_number) + "\n";
        rep += "\tType: " + std::to_string(type) + "\n";
        return rep;
    }



    // Token Stream
    TokenStream::TokenStream()
    {}

    TokenStream::~TokenStream()
    {}

    // increment ptr and get token at current pointer
    Token TokenStream::next() 
    {
        ptr++;
        if (ptr >= (int) stream.size())
            eof = true;
        return stream.at(ptr-1);
    }

    // Get char at current pointer
    Token TokenStream::peek() 
    {
        return stream.at(ptr);
    }

    // Print token stream
    void TokenStream::print() 
    {
        for (int i = 0; i < stream.size(); i++) 
        {
            Token tok = stream.at(i);
            std::cout << tok.repr() << std::endl;
        }
    }


} // namespace Sogolo

