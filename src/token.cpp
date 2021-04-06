#include "../include/token.hpp"


std::string Token::Token::repr()
{
    std::string rep;
    rep += "Token:\n";
    rep += "\tValue: '" + value + "'\n";
    rep += "\tLine: '" + line + "'\n";
    rep += "\tLine Number: " + std::to_string(line_number) + "\n";
    return rep;
}

void Token::TokenStream::print()
{
    for (int i = 0; i < stream.size(); i++)
    {
        Token tok = stream.at(i);
        std::cout << tok.repr() << std::endl;
    }
}