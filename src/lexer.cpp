#include "../include/lexer.hpp"

bool Lexer::is_important_char(char c)
{
    return (c == ';') || (c == '(') || (c == ')') || 
        (c == '[') || (c == ']') || 
        (c == '{') || (c == '}');
}


void Lexer::Lexer::tokenize()
{
    int line_number = 0;
    std::string current_line = code.lines.at(0);
    std::string str_value;

    // States
    bool in_string = false;

    for(int i = 0; i < code.str.length(); i++)
    {
        char chr = code.str.at(i);


        if (chr == '`')
        {
            str_value.push_back(chr);
            in_string = !in_string;
            if (in_string == false)
            {
                Token::Token tok;
                tok.value = str_value;
                tok.line = current_line;
                tok.line_number = line_number+1;
                stream.stream.push_back(tok);
                str_value = "";
            }
        }
        else if (in_string)
        {
            str_value.push_back(chr);
        }
        else if (isspace(chr))
        {
            if (str_value != "")
            {
                Token::Token tok;
                tok.value = str_value;
                tok.line = current_line;
                tok.line_number = line_number+1;
                stream.stream.push_back(tok);
                str_value = "";
            }
        }
        else if (is_important_char(chr))
        {
            if (str_value != "")
            {
                Token::Token tok;
                tok.value = str_value;
                tok.line = current_line;
                tok.line_number = line_number+1;
                stream.stream.push_back(tok);
                str_value = "";
            }
            Token::Token tok;
            tok.value.push_back(chr);
            tok.line = current_line;
            tok.line_number = line_number+1;
            stream.stream.push_back(tok);
        }
        else
        {
            str_value.push_back(chr);
        }

        if (chr == '\n')
        {
            line_number++;
            if (line_number != code.lines.size())
            {
                current_line = code.lines.at(line_number);
            }
        }
    }
}