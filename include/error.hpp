#ifndef FENNEC_ERROR_H
#define FENNEC_ERROR_H

#include "token.hpp"

namespace Parser
{
    enum error_type 
    {
        REGULAR,
        EOF_
    };

    class EOF_ERROR 
    {
    public:
        std::string msg;
        Token::Token token;
        std::string error();
    };

    class PARSING_ERROR 
    {
    public:
        std::string msg;
        Token::Token token;
        std::string error();
    };
}

#endif