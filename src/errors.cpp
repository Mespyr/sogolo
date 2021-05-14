#include "errors.hpp"

namespace Sogolo
{
    // EOF Error

    Error_EOF::Error_EOF(std::string& l, unsigned int ln)
    {
        line = l;
        line_number = ln;
    }
    
    Error_EOF::~Error_EOF()
    {}

    std::string Error_EOF::repr()
    {
        std::string msg = "EOF_Error on line " + std::to_string(line_number) + "\n";
        msg += "  " + line + "\n";
        msg += "Unexpected EOF while parsing.\n";
        return msg;
    }


    // Parsing Error

    Error_Parsing::Error_Parsing(std::string& l, unsigned int ln, std::string& m)
    {
        msg = m;
        line_number = ln;
        line = l;
    }
    
    Error_Parsing::~Error_Parsing()
    {}

    std::string Error_Parsing::repr()
    {
        std::string m = "Parsing_Error on line " + std::to_string(line_number) + ".\n";
        m += "  " + line + "\n";
        m += msg + "\n";
        return m;
    }

    void Error::set(ErrorType type, std::string& l, unsigned int ln, std::string& m)
    {
        if (type == ERROR_TYPE_EOF)
        {
            Error_EOF eof_error(l, ln);
            repr = eof_error.repr();
        }
        else if (type == ERROR_TYPE_PARSING)
        {
            Error_Parsing parsing_error(l, ln, m);
            repr = parsing_error.repr();
        }
    }

} // namespace Sogolo
