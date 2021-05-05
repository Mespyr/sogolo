#include "util.hpp"

namespace util {
    FileString read(std::string filename) {
        FileString string;
        std::ifstream file_handler;
        file_handler.open(filename);
        if (file_handler.is_open()) {
            string.exists = true;
            std::string line;
            while(getline(file_handler, line)) {
                string.str.lines.push_back(line);
                // std::cout << string.str.lines.back();
                string.str.str += line + "\n";
            }
            file_handler.close();
            string.str.str += "\0";
        }
        else
            string.exists = false;

        return string;
    }
} // namespace util
