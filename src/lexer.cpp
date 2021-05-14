#include "lexer.hpp"

namespace Sogolo
{
    // Lexer
    Lexer::Lexer(String c)
    {
        code = c;
        tokenize();
    }
    
    Lexer::~Lexer()
    {}

    // Move lexer to next char
    void Lexer::advance() 
    {
        idx++;
        if (idx < (int) code.str.length()-1) 
        {
            current_char = code.str.at(idx);
            if (current_char == '\n') 
            {
                line_number++;
                current_line = code.lines.at(line_number-1);
            }
        }
        else 
            eof = true;
    }

    // Move lexer to previous char
    void Lexer::stepdown() 
    {
        idx--;
        if (current_char == '\n') 
        {
            line_number--;
            current_line = code.lines.at(line_number-1);
        }
        current_char = code.str.at(idx);
    }

    // Generate number token
    void Lexer::make_number() 
    {
        std::string numeric;

        int dot_count = 0;

        numeric.push_back(current_char);

        while (!eof) 
        {
            advance();

            if (eof)
                break;
            
            if (current_char == '.') 
            {
                if (dot_count) 
                {
                    error_found = true;

                    em = "Unexpected '.' char found during lexical analysis.";
                    error.set(ERROR_TYPE_PARSING, current_line, line_number, em);
                }
                dot_count++;
            }

            else if (!isdigit(current_char)) 
            {
                if (
                    current_char == '(' || 
                    current_char == ')' ||
                    current_char == '[' ||
                    current_char == ']' ||
                    current_char == '{' ||
                    current_char == '}' ||
                    current_char == ';' ||
                    current_char == '#' ||
                    current_char == ',' ||
                    current_char == '\n'||
                    isspace(current_char)
                ) 
                {
                    stepdown();
                    break;
                }
                else 
                {
                    error_found = true;
                    // Setting Error msg
                    // should look like `Unexpected '<char>' char found during lexical analysis.`

                    em = "Unexpected '";
                    em.push_back(current_char);
                    em += "' char found during lexical analysis.";

                    error.set(ERROR_TYPE_PARSING, current_line, line_number, em);
                    return;
                }
            }
            
            numeric.push_back(current_char);
        }
        if (dot_count) 
            stream.stream.push_back(Token(TT_FLOAT, current_line, line_number, numeric));
        else
            stream.stream.push_back(Token(TT_INT, current_line, line_number, numeric));
        
    }

    // Generate symbol token
    void Lexer::make_symbol() 
    {
        std::string symbol;
        symbol.push_back(current_char);

        while (!eof) 
        {
            advance();

            if (eof)
                break;

            if (current_char == '(' || 
                current_char == ')' ||
                current_char == '[' ||
                current_char == ']' ||
                current_char == '{' ||
                current_char == '}' ||
                current_char == '{' ||
                current_char == ';' ||
                current_char == '#' ||
                current_char == ',' ||
                current_char == '\n'||
                isspace(current_char)
                ) 
                {
                    stepdown();
                    break;
                }
            if (current_char == '`')
            {
                error_found = true;
                em = "Unexpected '`' char found during lexical analysis.";
                error.set(ERROR_TYPE_PARSING, current_line, line_number, em);
            }

            symbol.push_back(current_char);
        }

        stream.stream.push_back(Token(TT_SYMBOL, current_line, line_number, symbol));
    }

    // Generate string token
    void Lexer::make_string() 
    {
        std::string string;
        string.push_back(current_char);

        while (!eof) 
        {
            advance();
            if (eof) 
            {
                error_found = true;
                error.set(ERROR_TYPE_EOF, current_line, line_number, em);
                return;
            }
            
            string.push_back(current_char);

            if (current_char == '`') 
                break;
        }
        stream.stream.push_back(Token(TT_STRING, current_line, line_number, string));
    }


    void Lexer::tokenize() 
    {
        current_line = code.lines.at(0);

        while (!eof) 
        {
            advance();
            if (eof) 
                break;

            if (in_comment) 
            {
                if (current_char == '\n')
                    in_comment = false;
                continue;
            }

            if (isspace(current_char)) 
                continue;
            
            switch (current_char)
            {
                case '#':
                    in_comment = true;
                    break;

                case ';':
                    stream.stream.push_back(Token(TT_SEMICOLON, current_line, line_number, ";"));
                    break;

                case ',':
                    stream.stream.push_back(Token(TT_COMMA, current_line, line_number, ","));
                    break;

                case '(':
                    stream.stream.push_back(Token(TT_LPAREN, current_line, line_number, "("));
                    break;

                case ')':
                    stream.stream.push_back(Token(TT_RPAREN, current_line, line_number, ")"));
                    break;

                case '[':
                    stream.stream.push_back(Token(TT_LBRACE, current_line, line_number, "["));
                    break;

                case ']':
                    stream.stream.push_back(Token(TT_RBRACE, current_line, line_number, "]"));
                    break;

                case '{':
                    stream.stream.push_back(Token(TT_LCBRACE, current_line, line_number, "{"));
                    break;

                case '}':
                    stream.stream.push_back(Token(TT_RCBRACE, current_line, line_number, "}"));
                    break;

                case '`':
                    make_string();
                    break;

                default:
                    if (isdigit(current_char)) 
                        make_number();
                    else
                        make_symbol();
                    break;
            }
        if (error_found)
            break;
        }
    }
} // namespace Sogolo
