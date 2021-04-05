#include "../include/util.hpp"


util::FileString util::read(std::string filename) 
{
    util::FileString string;
    std::ifstream file_handler;
    file_handler.open(filename);
    if (file_handler.is_open())
    {
        string.exists = true;
        std::string line;
        while(getline(file_handler, line))
        {
            string.str += line + "\n";
        }
        file_handler.close();
        string.str += "\0";
    }
    else
    {
        string.exists = false;
    }
    return string;
}