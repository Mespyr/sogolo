#ifndef ERRORS_H
#define ERRORS_H

#include <string>

namespace Sogolo
{
    enum ErrorType {
        ERROR_TYPE_EOF,
        ERROR_TYPE_PARSING
    };

    // EOF Error Class

    class Error_EOF
    {
    public:
        Error_EOF(std::string& l, unsigned int ln);
        ~Error_EOF();

        std::string line;
        unsigned int line_number;

        std::string repr();

    };

    // Parsing Error Class

    class Error_Parsing
    {
    public:
        Error_Parsing(std::string& l, unsigned int ln, std::string& m);
        ~Error_Parsing();

        std::string line;
        std::string msg;
        unsigned int line_number;

        std::string repr();
    };

    // Base Error Class

    class Error
    {
    public:
        Error() {}
        ~Error() {}

        void set(ErrorType t, std::string& l, unsigned int ln, std::string& m);

        std::string repr;
    };
} // namespace Sogolo


#endif