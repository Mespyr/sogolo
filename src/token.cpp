#include "../include/token.hpp"


std::string Token::Token::repr()
{
    return value + "  -  " + line + "  -  " + std::to_string(line_number);
}

void Token::TokenStream::print()
{
    for (int i = 0; i < stream.size(); i++)
    {
        Token tok = stream.at(i);
        std::cout << tok.repr() << std::endl;
    }
}