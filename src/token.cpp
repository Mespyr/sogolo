#include "../include/token.hpp"

namespace Token {
    std::string Token::repr() {
        std::string rep;
        rep += "Token:\n";
        rep += "\tValue: '" + value + "'\n";
        rep += "\tLine: '" + line + "'\n";
        rep += "\tLine Number: " + std::to_string(line_number) + "\n";
        return rep;
    }

    void TokenStream::print() {
        for (int i = 0; i < stream.size(); i++) {
            Token tok = stream.at(i);
            std::cout << tok.repr() << std::endl;
        }
    }

    Token TokenStream::next() {
        ptr++;
        if (ptr >= (int) stream.size())
            eof = true;
        return stream.at(ptr-1);
    }

    Token TokenStream::peek() {
        return stream.at(ptr);
    }
} // namespace Token