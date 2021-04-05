#include <iostream>
#include <fstream>
#include <string>

namespace util
{
    struct FileString
    {
        bool exists;
        std::string str;
    };

    FileString read(std::string filename);    
} // namespace util
