#include "util.hpp"

namespace Sogolo 
{
    File::File(const std::string& filename)
    {
        std::ifstream file_handler;
        file_handler.open(filename);
        if (file_handler.is_open()) 
        {
            exists = true;
            std::string line;
            while(getline(file_handler, line)) 
            {
                str.lines.push_back(line);
                str.str += line + "\n";
            }
            file_handler.close();
            str.str += "\0";
        }
        else
            exists = false;
    }
    
    File::~File()
    {}
} // namespace Sogolo
