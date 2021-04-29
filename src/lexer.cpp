#include "lexer.hpp"

namespace Lexer {
    void Lexer::advance() {
        idx++;
        if (idx < (int) code.str.length()-1) {
            current_char = code.str.at(idx);
            if (current_char == '\n') {
                line_number++;
                current_line = code.lines.at(line_number-1);
            }
        }
        else 
            eof = true;
    }

    void Lexer::skip_comment() {
        while (current_char != '\n' and !eof) {
            advance();
        }
    }

    void Lexer::tokenize() {
        current_line = code.lines.at(0);

        while (!eof) {
            advance();
            if (eof) break;
            if (isspace(current_char)) 
                continue;
            
            switch (current_char)
            {
                case '#':
                    skip_comment();
                    break;

                case ';':
                    stream.stream.push_back(Token::Token(Token::TT_SEMICOLON, current_line, line_number, ";"));
                    break;

                case ',':
                    stream.stream.push_back(Token::Token(Token::TT_COMMA, current_line, line_number, ","));
                    break;

                case '(':
                    stream.stream.push_back(Token::Token(Token::TT_LPAREN, current_line, line_number, "("));
                    break;

                case ')':
                    stream.stream.push_back(Token::Token(Token::TT_RPAREN, current_line, line_number, ")"));
                    break;

                case '[':
                    stream.stream.push_back(Token::Token(Token::TT_LBRACE, current_line, line_number, "["));
                    break;

                case ']':
                    stream.stream.push_back(Token::Token(Token::TT_RBRACE, current_line, line_number, "]"));

                case '{':
                    stream.stream.push_back(Token::Token(Token::TT_LCBRACE, current_line, line_number, "{"));
                    break;

                case '}':
                    stream.stream.push_back(Token::Token(Token::TT_RCBRACE, current_line, line_number, "}"));
                    break;

                default:
                    // if (isalnum(current_char)) 
                    //     make_number();
                    // else 
                    //     make_symbol();
                    break;
            }
        }
    }

} // namespace Lexer
